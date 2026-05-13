//
// Created by /<R3/<(RR00T on 13.05.2026.
//

#include "WidgetManager.h"

namespace SpaceLab::ui {

    WidgetManager::WidgetManager() = default;

    WidgetManager::~WidgetManager() {
        m_widgets.clear();
        m_widgets.shrink_to_fit();
    }

    void WidgetManager::addWidget(std::unique_ptr<SpaceLab::ui::Widget> widget) {
        m_widgets.push_back(std::move(widget));
    }

    Widget *WidgetManager::getWidgetAt(const glm::vec2 &pos) {
        for(auto it = m_widgets.rbegin(); it < m_widgets.rend(); ++it) {
            if((*it)->hit(pos)) {
                return it->get();
            }
        }

        return nullptr;
    }

    void WidgetManager::render(render::Renderer *renderer) {
        for(const auto& widget : m_widgets) {
            widget->draw();
        }
    }


} // SpaceLab