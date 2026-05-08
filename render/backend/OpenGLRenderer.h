//
// Created by /<R3/<(RR00T on 03.05.2026.
//

#ifndef SPACELABSTUDIO_OPENGLRENDERER_H
#define SPACELABSTUDIO_OPENGLRENDERER_H

//#include

#include <Renderer.h>

namespace SpaceLab {

    class OpenGLRenderer : public Renderer {

    public:
        void init(void *nativeWindow) override;

        void drawLine(Vector2<float> from, Vector2<float> to) override;

        void beginFrame() override;
        void endFrame() override;

    private:
        void flush() override;

    };

}

#endif //SPACELABSTUDIO_OPENGLRENDERER_H
