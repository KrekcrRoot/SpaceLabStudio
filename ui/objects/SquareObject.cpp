//
// Created by /<R3/<(RR00T on 09.05.2026.
//

#include "SquareObject.h"

namespace SpaceLab::ui {

    SquareObject::SquareObject(int i) :delta(i * 7) {}

    void SquareObject::draw(render::Renderer *renderer) {

        renderer->drawLine({0 + float(delta * 10), float(delta * 10)}, {0 + float(delta * 10), 50 + float(delta * 10)});
        renderer->drawLine({0 + float(delta * 10), 50 + float(delta * 10)}, {50 + float(delta * 10), 50 + float(delta * 10)});
        renderer->drawLine({50 + float(delta * 10), 50 + float(delta * 10)}, {50 + float(delta * 10), 0 + float(delta * 10)});
        renderer->drawLine({50 + float(delta * 10), 0 + float(delta * 10)}, {0 + float(delta * 10), 0 + float(delta * 10)});

        float outline = 5;
        Vector3<float> outlineColor = {0.f, 0.7f, 0.f};

        if(m_hover) {
            renderer->drawLine(
                {-outline + float(delta * 10), -outline + float(delta * 10)},
                {-outline + float(delta * 10), outline + 50 + float(delta * 10)},
                outlineColor
            );
            renderer->drawLine(
                {-outline + float(delta * 10), outline + 50 + float(delta * 10)},
                {outline + 50 + float(delta * 10), outline + 50 + float(delta * 10)},
                outlineColor
            );
            renderer->drawLine(
                {outline + 50 + float(delta * 10), outline + 50 + float(delta * 10)},
                {outline + 50 + float(delta * 10), -outline + float(delta * 10)},
                outlineColor
            );
            renderer->drawLine(
                {outline + 50 + float(delta * 10), -outline + float(delta * 10)},
                {-outline + float(delta * 10), -outline + float(delta * 10)},
                outlineColor
            );

        }

    }

    SquareObject::~SquareObject() noexcept = default;

    bool SquareObject::hit(const glm::vec2 &pos) const {

        auto bottom = float(delta * 10);
        float top = bottom + 50;
        auto left = float(delta * 10);
        float right = left + 50;

        if( (pos.x >= left && pos.x <= right) && (pos.y >= bottom && pos.y <= top) ) {
            return true;
        }

        return false;

    }

    void SquareObject::hover() {
        m_hover = true;
    }

    void SquareObject::leave() {
        m_hover = false;
    }

    void SquareObject::drag(const glm::vec2& _delta) {
//        m_drag = true;
    }

} // SpaceLab