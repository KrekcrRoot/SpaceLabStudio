#pragma once
#include <vector>
#include <stdint.h>

namespace ImageUtils {
    std::vector<uint8_t> flipVertical(const std::vector<uint8_t>& pixels, int width, int height);
    std::vector<float> toGrayscaleResized(const std::vector<uint8_t>& pixels, int srcW, int srcH, int targetW = 448, int targetH = 448);
}
