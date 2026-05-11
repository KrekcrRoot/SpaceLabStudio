//
// Created by /<R3/<(RR00T on 08.05.2026.
//

#include "InfiniteGrid.h"
#include <iostream>
#include <cmath>

namespace SpaceLab::ui {

    InfiniteGrid::InfiniteGrid() {
        backgroundColor.x *= 1.3;
        backgroundColor.y *= 1.3;
        backgroundColor.z *= 1.3;
    }

    void InfiniteGrid::render(SpaceLab::Renderer *renderer, Camera* camera) {

        float cell = 50.f;

        float x = floor(camera->left() / cell) * cell;
        float y = floor(camera->top() / cell) * cell;

//        float cmin = 0.2f, cmax = 0.25f;



        for(; x <= camera->right(); x += cell) {

//            renderer->drawLine({x, camera->top()}, {x, camera->bottom()}, {0.118,0.180,0.212});

            renderer->drawLine({x, camera->top()}, {x, camera->bottom()}, {
                sin(x) * (gridColor.x - backgroundColor.x) / 2 + (gridColor.x + backgroundColor.x) / 2,
                sin(x) * (gridColor.y - backgroundColor.y) / 2 + (gridColor.y + backgroundColor.y) / 2,
                sin(x) * (gridColor.z - backgroundColor.z) / 2 + (gridColor.z + backgroundColor.z) / 2,
            });
        }

        for(; y <= camera->bottom(); y += cell) {

//            renderer->drawLine({camera->left(), y}, {camera->right(), y}, {0.118,0.180,0.212});

            renderer->drawLine({camera->left(), y}, {camera->right(), y}, {
                sin(y) * (gridColor.x - backgroundColor.x) / 2 + (gridColor.x + backgroundColor.x) / 2,
                sin(y) * (gridColor.y - backgroundColor.y) / 2 + (gridColor.y + backgroundColor.y) / 2,
                sin(y) * (gridColor.z - backgroundColor.z) / 2 + (gridColor.z + backgroundColor.z) / 2,
            });
        }

    }

}