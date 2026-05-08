//
// Created by /<R3/<(RR00T on 03.05.2026.
//

#ifndef SPACELABSTUDIO_RENDERER_H
#define SPACELABSTUDIO_RENDERER_H

#include <math/objects/Vectors.h>

using namespace math;

namespace SpaceLab {
    class Renderer {
    public:

        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;

        virtual void drawLine(Vector2<float> from, Vector2<float> to) = 0;

        virtual void init(void *nativeWindow) = 0;

    private:
        virtual void flush() = 0;
    };
}


#endif //SPACELABSTUDIO_RENDERER_H
