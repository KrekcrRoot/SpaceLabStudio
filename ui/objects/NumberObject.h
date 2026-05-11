//
// Created by /<R3/<(RR00T on 09.05.2026.
//

#ifndef SPACELABSTUDIO_NUMBEROBJECT_H
#define SPACELABSTUDIO_NUMBEROBJECT_H

#include <objects/Object.h>
#include <Renderer.h>

namespace SpaceLab::ui {

    class NumberObject : public Object {

    public:
        NumberObject(const glm::vec2& pos, float length);
        void render(render::Renderer* renderer) override;

    };
}


#endif //SPACELABSTUDIO_NUMBEROBJECT_H
