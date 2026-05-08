file(GLOB RENDER_SOURCES */*.cpp)
file(GLOB RENDER_HEADERS */*.h)

add_library(render
        Renderer.h
        Renderer.cpp

        ${RENDER_SOURCES}
        ${RENDER_HEADERS}

        backend/OpenGLRenderer.cpp
        backend/OpenGLRenderer.h
)

target_include_directories(render
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(render
    platform
    math
)