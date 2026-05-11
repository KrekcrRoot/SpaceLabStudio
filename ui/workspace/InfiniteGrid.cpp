//
// Created by /<R3/<(RR00T on 08.05.2026.
//

#include "InfiniteGrid.h"
#include <iostream>
#include <cmath>

namespace SpaceLab::ui {

    void InfiniteGrid::render(SpaceLab::Renderer *renderer, Camera* camera) {

        float cell = 50.f;

        float x = floor(camera->left() / cell) * cell;
        float y = floor(camera->top() / cell) * cell;

        float cmin = 0.2f, cmax = 0.25f;

        for(; x <= camera->right(); x += cell) {
            renderer->drawLine({x, camera->top()}, {x, camera->bottom()}, {
                sin(x) * (cmax - cmin) / 2 + (cmin + cmax) / 2,
                sin(x) * (cmax - cmin) / 2 + (cmin + cmax) / 2,
                sin(x) * (cmax - cmin) / 2 + (cmin + cmax) / 2,
            });
        }

        for(; y <= camera->bottom(); y += cell) {
            renderer->drawLine({camera->left(), y}, {camera->right(), y}, {
                sin(y) * (cmax - cmin) / 2 + (cmin + cmax) / 2,
                sin(y) * (cmax - cmin) / 2 + (cmin + cmax) / 2,
                sin(y) * (cmax - cmin) / 2 + (cmin + cmax) / 2,
            });
        }

    }

}