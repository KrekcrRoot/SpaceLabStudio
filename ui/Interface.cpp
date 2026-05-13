//
// Created by /<R3/<(RR00T on 13.05.2026.
//

#include <Interface.h>

namespace SpaceLab::ui {

    void Interface::setup() {
//        m_mainLayer.addWidget();
    }

    void Interface::draw(render::Renderer *renderer) {
        m_mainLayer.render(renderer);
        m_overlayLayer.render(renderer);
    }

}