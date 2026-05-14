//
// Created by /<R3/<(RR00T on 13.05.2026.
//

#include <Interface.h>
#include <widgets/TextWidget.h>
#include <widgets/ButtonWidget.h>
#include <memory>

namespace SpaceLab::ui {

    void Interface::setup() {

        m_mainLayer.addWidget(
            std::make_unique<ui::TextWidget>(
                *m_fontManager->getByTitle("default"),
                glm::vec2 {300, 300},
                "some string lorem ipsum se dolor"
            )
        );

        m_mainLayer.addWidget(
            std::make_unique<ui::ButtonWidget>(
                glm::vec2 {0, 0},
                glm::vec2 {100, 100}
            )
        );

    }

    void Interface::draw(render::Renderer *renderer) {
        m_mainLayer.render(renderer);
        m_overlayLayer.render(renderer);
    }

}