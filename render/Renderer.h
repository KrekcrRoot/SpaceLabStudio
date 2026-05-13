//
// Created by /<R3/<(RR00T on 03.05.2026.
//

#ifndef SPACELABSTUDIO_RENDERER_H
#define SPACELABSTUDIO_RENDERER_H

#include "font/Font.h"
#include <math/objects/Vectors.h>
#include <glm/glm.hpp>

using namespace math;

namespace SpaceLab::render {
    class Renderer {
    public:

        virtual ~Renderer() = default;

        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;

        virtual void beginUI() = 0;
        virtual void endUI() = 0;

        virtual void setViewProjection(glm::mat4 projectionMatrix) = 0;

        virtual void drawLine(Vector2<float> from, Vector2<float> to) = 0;
        virtual void drawLine(Vector2<float> from, Vector2<float> to, Vector3<float> color) = 0;
        virtual void drawLine(Vector2<float> from, Vector2<float> to, Vector3<float> color, float alpha) = 0;
        virtual void drawGradientLine(Vector4<float> pos, Vector4<float> fromColor, Vector4<float> toColor) = 0;

        // Text Rendering
        virtual void drawString(const font::Font& font, const std::string& str, Vector2<float> pos) = 0;

        virtual void init(void *nativeWindow) = 0;

    private:
        virtual void flush() = 0;
    };
}


#endif //SPACELABSTUDIO_RENDERER_H
