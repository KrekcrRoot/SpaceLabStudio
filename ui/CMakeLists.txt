file(GLOB UI_HEADERS *.h)

file(GLOB UI_OBJECTS_HEADERS objects/*.h)
file(GLOB UI_OBJECTS_SOURCES objects/*.cpp)

add_library(ui
    workspace/InfiniteGrid.h
    workspace/InfiniteGrid.cpp
    ${UI_HEADERS}

    ${UI_OBJECTS_HEADERS}
    ${UI_OBJECTS_SOURCES}
)

target_include_directories(ui
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ui
    render
)