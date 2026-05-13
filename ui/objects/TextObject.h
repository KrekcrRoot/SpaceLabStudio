//
// Created by /<R3/<(RR00T on 11.05.2026.
//

#ifndef SPACELABSTUDIO_TEXTOBJECT_H
#define SPACELABSTUDIO_TEXTOBJECT_H

#include <font/Font.h>
#include <objects/Object.h>

namespace SpaceLab::ui {

    class TextObject : public Object {

    public:
        TextObject(render::font::Font *font, std::string str);
        void render(render::Renderer* renderer) override;

    private:
        std::string m_text;
        render::font::Font *m_font;

    };

}

#endif //SPACELABSTUDIO_TEXTOBJECT_H
