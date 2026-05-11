//
// Created by /<R3/<(RR00T on 11.05.2026.
//

#ifndef SPACELABSTUDIO_FONT_H
#define SPACELABSTUDIO_FONT_H

#include <math/objects/Vectors.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>


namespace SpaceLab::render::font {

    struct Glyph {
        float ax, ay;
        float bw, bh;
        float bl, bt;
        float tx, ty, tw, th;
    };

    class Font {

    public:
        Font() = default;
        ~Font();

        bool load(const char* ttfPath, float fontSize);
        void buildString(const std::string& text, math::Vector2<float> pos, std::vector<float>& outVertices) const;

        [[nodiscard]] GLuint getTexture() const;
        [[nodiscard]] float getFontSize() const;

    private:
        GLuint m_tex = 0;
        float m_fontSize = 0;
        int m_atlasWidth = 512, m_atlasHeight = 512;
        std::unordered_map<char, Glyph> m_glyphs;
        float m_ascent = 0;

    };

}

#endif //SPACELABSTUDIO_FONT_H
