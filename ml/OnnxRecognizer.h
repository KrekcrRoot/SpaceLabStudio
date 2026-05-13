// First version: 2024-06-01 W1AS

#pragma once
#include <string>
#include <vector>
#include <stdint.h>
#include <memory>

using namespace std;

class OnnxRecognizer
{
    public:

    explicit OnnxRecognizer(const string& modelDir);
    ~OnnxRecognizer();
    string recognize(const vector<uint8_t>& pixels, int w, int h);

    private:

    struct Impl;
    unique_ptr<Impl>  impl;
    vector<string> loadVocab(const string& path);
    int decoderStep(const vector<float>& encoderHidden, const vector<int64_t>& inputIds);
};
