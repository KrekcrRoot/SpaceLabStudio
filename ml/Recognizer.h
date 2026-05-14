#pragma once
#include <string>
#include <vector>
#include <stdint.h>
#include <memory>

class OnnxRecognizer;

namespace SpaceLab {
class Recognizer {
public:
    explicit Recognizer(const std::string& modelsDir = "assets/models");
    ~Recognizer();
    std::string recognize(const std::vector<uint8_t>& pixels, int w, int h);
private:
    std::unique_ptr<OnnxRecognizer> backend;
};
} // namespace SpaceLab
