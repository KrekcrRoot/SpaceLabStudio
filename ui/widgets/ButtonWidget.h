//
// Created by /<R3/<(RR00T on 14.05.2026.
//

#ifndef SPACELABSTUDIO_BUTTONWIDGET_H
#define SPACELABSTUDIO_BUTTONWIDGET_H

#include <widgets/Widget.h>
#include <Renderer.h>

namespace SpaceLab::ui {

    class ButtonWidget : public Widget {

    public:
        ButtonWidget(const glm::vec2& pos, const glm::vec2& size);

        void setText(const std::string& text);
        [[nodiscard]] const std::string& getText() const;

        void draw(render::Renderer *renderer) override;

    private:
        std::string m_text;


    };

}

#endif //SPACELABSTUDIO_BUTTONWIDGET_H
