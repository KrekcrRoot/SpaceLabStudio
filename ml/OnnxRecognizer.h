#pragma once
#include <string>
#include <vector>
#include <stdint.h>
#include <memory>

class OnnxRecognizer {
public:
    explicit OnnxRecognizer(const std::string& modelsDir);
    ~OnnxRecognizer();
    std::string recognize(const std::vector<uint8_t>& pixels, int w, int h);

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
    std::vector<std::string> loadVocab(const std::string& path);
    int decoderStep(const std::vector<float>& encoderHidden, const std::vector<int64_t>& inputIds);
};
