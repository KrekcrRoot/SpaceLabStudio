add_library(platform
        Window.h
        Window.cpp
        Platform.h
)

target_include_directories(platform
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(platform glfw)