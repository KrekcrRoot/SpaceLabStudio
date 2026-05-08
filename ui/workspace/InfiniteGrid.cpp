//
// Created by /<R3/<(RR00T on 08.05.2026.
//

#include "InfiniteGrid.h"
#include <iostream>
#include <cmath>

namespace SpaceLab::ui {

    void InfiniteGrid::render(SpaceLab::Renderer *renderer, Camera* camera) {

//        std::cout << camera->right() << "\n";

        float cell = 50.f;

        float x = floor(camera->left() / cell) * cell;
        float y = floor(camera->top() / cell) * cell;

        for(; x <= camera->right(); x += 50) {
            renderer->drawLine({x, camera->top()}, {x, camera->bottom()}, {fmax(0.2f * sin(x * 2), 0.14f), fmax(0.2f * sin(x * 2), 0.14f), fmax(0.2f * sin(x * 2), 0.14f)});
        }

        for(; y <= camera->bottom(); y += 50) {
            renderer->drawLine({camera->left(), y}, {camera->right(), y}, {fmax(0.2f * sin(y * 2), 0.14f), fmax(0.2f * sin(y * 2), 0.14f), fmax(0.2f * sin(y * 2), 0.14f)});
        }

    }

}