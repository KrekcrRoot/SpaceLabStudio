// First version: 2024-06-01 W1AS

#include "OnnxRecognizer.h"
#include "ImageUtils.h"
#include <onnxruntime_cxx_api.h>
#include <nlohmann/json.hpp>

#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <stdio.h>

using namespace std;
using json = nlohmann::json;

static constexpr int IMG_W = 448;
static constexpr int IMG_H = 448;
static constexpr int VOCAB_SIZE = 15000;
static constexpr int MAX_SEG = 512;
static constexpr int64_t = BOS = 0;
static constexpr int64_t = EOS = 2;

struct OnnxRecognizer::Impl {
    Ort::Env env{ORT_LOGGING_LEVEL_WARNING, "TexTeller:"};
    Ort::SessionOptions opts;
    Ort::AllocatorWithDefaultOptions allocator;

    unique_ptr<Ort::Session> encoderSession;
    unique_ptr<Ort::Session> decoderSession;

    vector<string> vocab;
};

OnnxRecognizer::OnnxRecognizer(const string& modelDir) : impl(make_unique<Impl>())
{
    impl->opts.SetIntraOpNumThreads(0);

    string encPath = modelDir + "/encoder_model_int8.onnx";
    string decPath = modelDir + "/decoder_model_int8.onnx";
    string tokPath = modelDir + "/tokonizer.json";

    printf("[ML] Загрузка говна... \n")
    impl->encoderSession = make_unique<Ort::Session>(impl->env, encPath.c_str(), impl->opts);

    printf("[ML] Как я заебался... \n")
    impl->decoderSession = make_unique<Ort::Session>(impl->env, decPath.c_str(), impl->opts);

    impl->vocab = loadVocab(tokPath);

    printf("[ML] Готово. Словарь: %zu токенов\n", impl->vocab.size());
}

OnnxRecognizer::~OnnxRecognizer() = default;

vector<string> OnnxRecognizer::loadVocab(const string& path)
{
    ifstream f(path);
    if (!f.is_open())
        throw runtime_error("[ML] Иди нахуй со своим tokenizer: " + path);
    
    json tok = json::parse(f);
    auto& vocabMap = tok["model"]["vocab"];
    vector<string> vocab;

    for (auto& [token, idJson] : vocabMap.items()) 
    {
        int id = idJson.get<int>();
        if (id >= (int)vocab.size()) vocab.resize(id + 1);
        vocab[id] = token;
    }
    return vocab;
}

static Ort::Value makeFloat(Ort::MemoryInfo& mem, vector<float>& data, vector<int64_t> shape) 
{
    size_t n = 1;
    for (auto d : shape) n *= (size_t)d;
    return Ort::Value::CreateTensor<float>(mem, data.data(), n, shape.data(), shape.size());
}

int OnnxRecognizer::decoderStep(const vector<float>& encoderHidden, const vector<int64_t>& inputIds) 
{
    auto mem = Ort::MemoryInfo::CreateCpu(openArenaAllocator, OrtMemTypeDefault);
    int seqLen = (int)inputIds.size();

    vector<float> encCopy = encoderHidden;
    vector<int64_t> encShape = {1, ENC_SEQ, ENC_DIM};
    auto encTensor = makeFloat(mem, encCopy, encShape);

    vector<int64_t> idsCopy = inputIds;
    vector<int64_t> idsShape = {1, seqLen};
    auto idsTEnsor = Ort::Value::CreateTensor<int64_t>(mem, idsCopy.data(), idsCopy.size(), idsShape.data(), idsShape.size());

    const char* inNames[] = {"input_ids", "encoder_hidden_states"};
    const char* outNames[] = {"logits"};

    Ort::Value inputs[] = {move(idsTensor), move(encTensor)};

    auto out = impl->decoderSession->Run(Ort::RunOptions{nullptr}, inNames, inputs, 2, outNames, 1);

    float* logits = out[0].GetTensorMutableData<float>();
    float* lastPos = logits + (seqLen - 1) * VOCAB_SIZE;

    return (int)(max_element(lastPos, lastPos + VOCAB_SIZE) - latPos);
}

string OnnxRecognizer::recognize(const vector<uint8_t>& pixels, int w, int h)
{
    auto mem = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    auto flipped = ImageUtils::flipVertical(pixels, w, h);
    auto gray = Imageutils::toGrayscaleResized(flipped, w, h, IMG_W, IMG_H);

    vector<int64_t> imgShape = {1, 1, IMG_H, IMG_W};
    auto imgTensor = makeFloat(mem, gray, imgShape);

    const char* encIn[] = {"pixel_values"};
    const char* encout[] = {"last_hidden_state"};

    auto encOutputs = impl->encoderSession->Run(Ort::RunOptions{nullptr}, encIn, &imgTensor, 1, encOut, 1);

    float* encPtr = encOutputs[0].GetTensorMutableData<float>();
    vector<int64_t> tokenIds = {BOS};

    for (int strp = 0; step < MAX_SEQ; step++)
    {
        int next = decoderStep(encoderHidden, tokenIds);
        if (next== EOS) break;

        tokenIds.push_back((int64_t)next);
    }
    string result;
    for (size_t i = 1; i < tokenIds.size(); i++) {
        int64_t id = tokenIds[i];

        // Проверяем что id в пределах словаря и токен не пустой
        if (id < (int64_t)impl->vocab.size() && !impl->vocab[id].empty()) {
            result += impl->vocab[id];
        }
    }
    return result.empty() ? "ERROR: пустой результат" : result; 
}