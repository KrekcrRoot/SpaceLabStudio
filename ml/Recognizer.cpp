#include "Recognizer.h"
#include "OnnxRecognizer.h"

namespace SpaceLab {

Recognizer::Recognizer(const std::string& modelsDir)
    : backend(std::make_unique<OnnxRecognizer>(modelsDir)) {}

Recognizer::~Recognizer() = default;

std::string Recognizer::recognize(const std::vector<uint8_t>& pixels, int w, int h) {
    return backend->recognize(pixels, w, h);
}

} // namespace SpaceLab
