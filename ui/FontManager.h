//
// Created by /<R3/<(RR00T on 13.05.2026.
//

#ifndef SPACELABSTUDIO_FONTMANAGER_H
#define SPACELABSTUDIO_FONTMANAGER_H

#include <map>
#include <font/Font.h>

namespace SpaceLab::ui {

    class FontManager {

    public:
        FontManager() = default;
        ~FontManager() {
            for(const auto& [str, font] : m_fonts) {
                delete font;
            }
        }

        void addFont(const std::string& title, render::font::Font *font) {
            m_fonts[title] = font;
        }

        render::font::Font* getByTitle(const std::string& title) {
            return m_fonts[title];
        }

    private:
        std::map<std::string, render::font::Font*> m_fonts;

    };

}


#endif //SPACELABSTUDIO_FONTMANAGER_H
