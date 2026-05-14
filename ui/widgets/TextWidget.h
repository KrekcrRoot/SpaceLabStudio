//
// Created by /<R3/<(RR00T on 13.05.2026.
//

#ifndef SPACELABSTUDIO_TEXTWIDGET_H
#define SPACELABSTUDIO_TEXTWIDGET_H

#include <Renderer.h>
#include <widgets/Widget.h>

namespace SpaceLab::ui {

    class TextWidget : public Widget {

    public:
        TextWidget(const render::font::Font &font, const glm::vec2& pos, const std::string& str);
        void draw(render::Renderer* renderer) override;

    private:

        const render::font::Font& m_font;
        const std::string& m_text;

    };

}

#endif //SPACELABSTUDIO_TEXTWIDGET_H
