//
// Created by /<R3/<(RR00T on 08.05.2026.
//

#ifndef SPACELABSTUDIO_INFINITEGRID_H
#define SPACELABSTUDIO_INFINITEGRID_H

#include <Renderer.h>
#include <Camera.h>

namespace SpaceLab::ui {

    class InfiniteGrid {

    public:
        InfiniteGrid();
        void render(render::Renderer* renderer, render::Camera* camera) const;

    private:

        const Vector3<float> gridColor = {0.118,0.180,0.212};
        Vector3<float> backgroundColor = {0.063,0.086,0.110};

    };

}

#endif //SPACELABSTUDIO_INFINITEGRID_H
