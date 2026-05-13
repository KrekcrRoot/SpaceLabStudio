// First version: 2024-06-01 W1AS

#pragma once
#include <vector>
#include <stdint.h>

using namespace std;

namespace ImageUtils
{
    vector<uint8_t> flipvertical(const vector<uint8_t>& pixels, int width, int height);
    vector<float> toGayscaleResized(const vector<uint8_t>& pixels, int srcW, int srcH, int targetW = 448, int targetH = 488);
} // namespace ImageUtils

