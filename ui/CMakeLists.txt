file(GLOB UI_HEADERS *.h)
file(GLOB UI_SOURCES *.cpp)

file(GLOB UI_OBJECTS_HEADERS objects/*.h)
file(GLOB UI_OBJECTS_SOURCES objects/*.cpp)

file(GLOB UI_WIDGETS_HEADERS widgets/*.h)
file(GLOB UI_WIDGETS_SOURCES widgets/*.cpp)

add_library(ui
    workspace/InfiniteGrid.h
    workspace/InfiniteGrid.cpp
    ${UI_HEADERS}
    ${UI_SOURCES}

    ${UI_OBJECTS_HEADERS}
    ${UI_OBJECTS_SOURCES}

    ${UI_WIDGETS_HEADERS}
    ${UI_WIDGETS_SOURCES}
)

target_include_directories(ui
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ui
    render
)