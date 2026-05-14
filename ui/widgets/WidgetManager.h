//
// Created by /<R3/<(RR00T on 13.05.2026.
//

#ifndef SPACELABSTUDIO_WIDGETMANAGER_H
#define SPACELABSTUDIO_WIDGETMANAGER_H

#include <Renderer.h>
#include <FontManager.h>
#include <widgets/Widget.h>
#include <glm/glm.hpp>
#include <vector>

namespace SpaceLab::ui {
    class WidgetManager {

    public:
        explicit WidgetManager(FontManager* fontManager);
        ~WidgetManager();

        void addWidget(std::unique_ptr<Widget> widget);

        Widget* getWidgetAt(const glm::vec2& pos);

        void render(render::Renderer *renderer);


    private:
        std::vector<std::unique_ptr<Widget>> m_widgets;
        FontManager* m_fontManager;


    };
} // SpaceLab

#endif //SPACELABSTUDIO_WIDGETMANAGER_H
