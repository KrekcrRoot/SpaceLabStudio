#include "Recognizer.h"
#include "OnnxRecognizer.h"

namespace SpaceLab 
{
    Recognizer::Recognizer(const string& modelsDir) : backend(make_unique<OnnxRecognizer>(modelsDir)){}
    Recognizer::~Recognizer() = default;

    string Recognizer::recognize(const vector<uint8_t>& pixels, int w, int h)
    {
        return backend->recognize(pixels, w, h);
    }
}