//
// Created by /<R3/<(RR00T on 11.05.2026.
//

#define STB_TRUETYPE_IMPLEMENTATION

#include <math/objects/Vectors.h>
#include <stb_truetype.h>
#include <font/Font.h>
#include <fstream>
#include <iostream>



namespace SpaceLab::render::font {

    using namespace math;

    Font::~Font() {
        if(m_tex)
            glDeleteTextures(1, &m_tex);
    }

    bool Font::load(const char *ttfPath, float fontSize) {

        std::ifstream file(ttfPath, std::ios::binary | std::ios::ate);

        if(!file) {
            std::cerr << "Font file not found: " << ttfPath << std::endl;
            return false;
        }

        std::streamsize size = file.tellg();
        file.seekg(0);
        std::vector<unsigned char> buffer(size);
        file.read(reinterpret_cast<char*>(buffer.data()), size);
        file.close();

        stbtt_fontinfo info;
        if(!stbtt_InitFont(&info, buffer.data(), 0)) {
            std::cerr << "Failed to init font" << std::endl;
            return false;
        }

        m_fontSize = fontSize;
        float scale = stbtt_ScaleForPixelHeight(&info, fontSize);
        int ascent, descent, lineGap;
        stbtt_GetFontVMetrics(&info, &ascent, &descent, &lineGap);
        m_ascent = (float) ascent * scale;
        m_descent = (float) descent * scale;

        std::vector<unsigned char> atlas(m_atlasWidth * m_atlasHeight, 0);
        int x = 1, y = 1, rowHeight = 0;

        m_glyphs.clear();
        for (int c = 32; c < 128; ++c) {
            int w, h, xoff, yoff;
            unsigned char* bmp = stbtt_GetCodepointBitmap(&info, scale, scale, c, &w, &h, &xoff, &yoff);

            if(!bmp)
                continue;

            if(x + w + 1 >= m_atlasWidth) {
                y += rowHeight + 1;
                x = 1;
                rowHeight = 0;
            }

            for (int j = 0; j < h; ++j) {
                for(int i = 0; i < w; ++i) {
                    atlas[(y + j) * m_atlasWidth + (x + i)] = bmp[j * w + i];
                }
            }
            stbtt_FreeBitmap(bmp, nullptr);

            int advance, lsb;
            stbtt_GetCodepointHMetrics(&info, c, &advance, &lsb);

            Glyph g {};
            g.ax = (float) advance * scale;
            g.bw = static_cast<float>(w);
            g.bh = static_cast<float>(h);
            g.bl = static_cast<float>(xoff);
            g.bt = static_cast<float>(yoff);
            g.tx = x / static_cast<float>(m_atlasWidth);
            g.ty = y / static_cast<float>(m_atlasHeight);
            g.tw = w / static_cast<float>(m_atlasWidth);
            g.th = h / static_cast<float>(m_atlasHeight);
            m_glyphs[static_cast<char>(c)] = g;

            x += w + 1;
            if(h > rowHeight)
                rowHeight = h;

        }

        {
            int advance, lsb;
            stbtt_GetCodepointHMetrics(&info, ' ', &advance, &lsb);
            Glyph spaceGlyph{};
            spaceGlyph.ax = (float) advance * scale;
            spaceGlyph.bw = 0;
            spaceGlyph.bh = 0;
            spaceGlyph.bl = 0;
            spaceGlyph.bt = 0;
            spaceGlyph.tx = 0;
            spaceGlyph.ty = 0;
            spaceGlyph.tw = 0;
            spaceGlyph.th = 0;
            m_glyphs[' '] = spaceGlyph;
        }

        glGenTextures(1, &m_tex);
        glBindTexture(GL_TEXTURE_2D, m_tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_atlasWidth, m_atlasHeight, 0, GL_RED, GL_UNSIGNED_BYTE, atlas.data());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            std::cerr << "OpenGL error after font texture: " << err << std::endl;
        }

        glBindTexture(GL_TEXTURE_2D, 0);

        return true;
    }

    void Font::buildString(const std::string& text, Vector2<float> pos, std::vector<float>& outVertices) const {
        outVertices.clear();

        float penX = pos.x;
        float penY = pos.y;

        for (char c : text) {
            auto it = m_glyphs.find(c);
            if (it == m_glyphs.end())
                it = m_glyphs.find('?');

            if (it == m_glyphs.end()) continue;

            const Glyph& g = it->second;
            if (g.bw == 0.0f && g.bh == 0.0f) {
                penX += g.ax;
                continue;
            }
            float x0 = penX + g.bl;
            float y0 = penY - g.bt;
            float x1 = x0 + g.bw;
            float y1 = y0 - g.bh;

            float verts[] = {
                x0, y0, g.tx, g.ty,
                x0, y1, g.tx, g.ty + g.th,
                x1, y1, g.tx + g.tw, g.ty + g.th,
                x0, y0, g.tx, g.ty,
                x1, y1, g.tx + g.tw, g.ty + g.th,
                x1, y0, g.tx + g.tw, g.ty
            };

            outVertices.insert(outVertices.end(), verts, verts + 24);
            penX += g.ax;
        }

    }

    glm::vec2 Font::measureString(const std::string &text) const {
        float width = 0.0f;
        for (char c : text) {
            auto it = m_glyphs.find(c);
            if (it == m_glyphs.end()) it = m_glyphs.find('?');
            if (it == m_glyphs.end()) continue;
            width += it->second.ax;
        }

        float height = m_ascent - m_descent;
        return {width, height};
    }

    GLuint Font::getTexture() const {
        return m_tex;
    }

    float Font::getFontSize() const {
        return m_fontSize;
    }

}