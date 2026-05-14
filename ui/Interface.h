//
// Created by /<R3/<(RR00T on 13.05.2026.
//

#ifndef SPACELABSTUDIO_INTERFACE_H
#define SPACELABSTUDIO_INTERFACE_H

#include <widgets/widgets.h>
#include <Renderer.h>

namespace SpaceLab::ui {

    class Interface {
    public:
        explicit Interface(FontManager* fontManager) :
            m_mainLayer(fontManager), m_overlayLayer(fontManager), m_fontManager(fontManager)
        {
            setup();
        }

        void setup();
        void draw(render::Renderer *renderer);

    private:

        FontManager *m_fontManager;
        WidgetManager m_mainLayer;
        WidgetManager m_overlayLayer;

    };

}

#endif //SPACELABSTUDIO_INTERFACE_H
