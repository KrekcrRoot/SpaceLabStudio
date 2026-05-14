#include "OnnxRecognizer.h"
#include "ImageUtils.h"
#include <onnxruntime_cxx_api.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <stdio.h>

using json = nlohmann::json;

static constexpr int     IMG_W      = 448;
static constexpr int     IMG_H      = 448;
static constexpr int     ENC_SEQ    = 785;
static constexpr int     ENC_DIM    = 768;
static constexpr int     VOCAB_SIZE = 15000;
static constexpr int     MAX_SEQ    = 512;
static constexpr int64_t BOS        = 0;
static constexpr int64_t EOS        = 2;

struct OnnxRecognizer::Impl {
    Ort::Env            env{ORT_LOGGING_LEVEL_WARNING, "TexTeller"};
    Ort::SessionOptions opts;
    Ort::AllocatorWithDefaultOptions allocator;
    std::unique_ptr<Ort::Session> encoderSession;
    std::unique_ptr<Ort::Session> decoderSession;
    std::vector<std::string> vocab;
};

OnnxRecognizer::OnnxRecognizer(const std::string& modelsDir)
    : impl(std::make_unique<Impl>())
{
    impl->opts.SetIntraOpNumThreads(0);
    std::string encPath = modelsDir + "/encoder_model.onnx";
    std::string decPath = modelsDir + "/decoder_model.onnx";
    std::string tokPath = modelsDir + "/tokenizer.json";
    printf("[ML] Загружаю encoder...\n");
    impl->encoderSession = std::make_unique<Ort::Session>(impl->env, encPath.c_str(), impl->opts);
    printf("[ML] Загружаю decoder...\n");
    impl->decoderSession = std::make_unique<Ort::Session>(impl->env, decPath.c_str(), impl->opts);
    impl->vocab = loadVocab(tokPath);
    printf("[ML] Готово. Словарь: %zu токенов\n", impl->vocab.size());
}

OnnxRecognizer::~OnnxRecognizer() = default;

std::vector<std::string> OnnxRecognizer::loadVocab(const std::string& path) {
    std::ifstream f(path);
    if (!f.is_open())
        throw std::runtime_error("[ML] Не удалось открыть: " + path);
    json tok = json::parse(f);
    auto& vocabMap = tok["model"]["vocab"];
    std::vector<std::string> vocab;
    for (auto& [token, idJson] : vocabMap.items()) {
        int id = idJson.get<int>();
        if (id >= (int)vocab.size()) vocab.resize(id + 1);
        vocab[id] = token;
    }
    return vocab;
}

static Ort::Value makeFloat(Ort::MemoryInfo& mem, std::vector<float>& data, std::vector<int64_t> shape) {
    size_t n = 1;
    for (auto d : shape) n *= (size_t)d;
    return Ort::Value::CreateTensor<float>(mem, data.data(), n, shape.data(), shape.size());
}

int OnnxRecognizer::decoderStep(const std::vector<float>& encoderHidden, const std::vector<int64_t>& inputIds) {
    auto mem = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    int seqLen = (int)inputIds.size();
    std::vector<float>   encCopy  = encoderHidden;
    std::vector<int64_t> encShape = {1, ENC_SEQ, ENC_DIM};
    auto encTensor = makeFloat(mem, encCopy, encShape);
    std::vector<int64_t> idsCopy  = inputIds;
    std::vector<int64_t> idsShape = {1, seqLen};
    auto idsTensor = Ort::Value::CreateTensor<int64_t>(mem, idsCopy.data(), idsCopy.size(), idsShape.data(), idsShape.size());
    const char* inNames[]  = {"input_ids", "encoder_hidden_states"};
    const char* outNames[] = {"logits"};
    Ort::Value inputs[] = {std::move(idsTensor), std::move(encTensor)};
    auto out = impl->decoderSession->Run(Ort::RunOptions{nullptr}, inNames, inputs, 2, outNames, 1);
    float* logits  = out[0].GetTensorMutableData<float>();
    float* lastPos = logits + (seqLen - 1) * VOCAB_SIZE;
    return (int)(std::max_element(lastPos, lastPos + VOCAB_SIZE) - lastPos);
}

std::string OnnxRecognizer::recognize(const std::vector<uint8_t>& pixels, int w, int h) {
    auto mem = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    auto flipped = ImageUtils::flipVertical(pixels, w, h);
    auto gray    = ImageUtils::toGrayscaleResized(flipped, w, h, IMG_W, IMG_H);
    std::vector<int64_t> imgShape = {1, 1, IMG_H, IMG_W};
    auto imgTensor = makeFloat(mem, gray, imgShape);
    const char* encIn[]  = {"pixel_values"};
    const char* encOut[] = {"last_hidden_state"};
    auto encOutputs = impl->encoderSession->Run(Ort::RunOptions{nullptr}, encIn, &imgTensor, 1, encOut, 1);
    float* encPtr = encOutputs[0].GetTensorMutableData<float>();
    std::vector<float> encoderHidden(encPtr, encPtr + ENC_SEQ * ENC_DIM);
    std::vector<int64_t> tokenIds = {BOS};
    for (int step = 0; step < MAX_SEQ; step++) {
        int next = decoderStep(encoderHidden, tokenIds);
        if (next == EOS) break;
        tokenIds.push_back((int64_t)next);
    }
    std::string result;
    for (size_t i = 1; i < tokenIds.size(); i++) {
        int64_t id = tokenIds[i];
        if (id < (int64_t)impl->vocab.size() && !impl->vocab[id].empty())
            result += impl->vocab[id];
    }
    return result.empty() ? "ERROR: пустой результат" : result;
}
