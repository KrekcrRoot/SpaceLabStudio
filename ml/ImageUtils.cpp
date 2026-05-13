// First version: 2024-06-01 W1AS

#include "ImageUtils.h"
#include <algorithm>

using namespace std;

namespace ImageUtils
{
    vector<uint8_t> flipvertical(const vector<uint8_t>& pixels, int width, int height)
    {
        vector<uint8_t> flipped(pixels.size());
        int rowBytes = width * 4;

        for (int y = 0; y < height; ++y) 
        {
            memccpy(flipped.data() + y * rowBytes, pixels.data() + (height - 1 - y) * rowBytes, rowBytes);
        }
        return flipped;
    }   
    vector<float> toGrayscaleResized(const vector<uint8_t>& pixels, int srcW, int srcH, int targetW, int targetH)
    {
        vector<float> result(targetW * targetH);
        float scaleX = static_cast<float>(srcW) / targetW;
        float scaleY = static_cast<float>(srcH) / targetH;

        for (int y = 0; y < targetH; y++)
        {
            for (int x = 0; x < targetW; x++)
            {
                int sx = static_cast<int>(x * scaleX);
                int sy = static_cast<int>(y * scaleY);
                int idx = (sy * srcW + sx) * 4;
                
                uint8_t r = pixels[idx + 0];
                uint8_t g = pixels[idx + 1];
                uint8_t b = pixels[idx + 2];

                float gray = (0.299f * r + 0.587f * g + 0.114f * b) / 255.0f;
                result[y * targetW + x] = gray * 2.0f - 1.0f;
            }
        }
        return result;
    }
} // namespace ImageUtils
