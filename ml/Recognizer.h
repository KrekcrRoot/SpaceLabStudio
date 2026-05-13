// First version: 2024-06-01 W1AS

#pragma once
#include <string>
#include <vector>
#include <stdint.h>
#include <memory>

using namespace std;

class OnnxRecognizer;

namespace SpaceLab 
{
    class Recognizer 
    {
        public:

        explicit Recognizer(const string& modelsDir = "assets/models");
        ~Recognizer();
        string recognize(const vector<uint8_t>& pixels, int w, int h);

        private:

        unique_ptr<OnnxRecognizer> backend;
    };
} //namespcae SpaceLab