//
// Created by /<R3/<(RR00T on 09.05.2026.
//

#ifndef SPACELABSTUDIO_SQUAREOBJECT_H
#define SPACELABSTUDIO_SQUAREOBJECT_H

#include <Sprite.h>

namespace SpaceLab::ui {

    class SquareObject : public Sprite {

    public:
        explicit SquareObject(int i);
        void draw(render::Renderer* renderer) override;
        ~SquareObject() override;

        [[nodiscard]] bool hit(const glm::vec2& pos) const override;

        void hover() override;
        void leave() override;
        void drag(const glm::vec2& delta) override;

    private:
        int delta;

    };

} // SpaceLab

#endif //SPACELABSTUDIO_SQUAREOBJECT_H
