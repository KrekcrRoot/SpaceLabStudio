cmake_minimum_required(VERSION 4.0)
project(SpaceLabStudio)

include_directories(third_party/glad/include)
add_subdirectory(third_party/glfw-3.4)

add_subdirectory(render)
add_subdirectory(app)
add_subdirectory(platform)
add_subdirectory(math)

set(CMAKE_CXX_STANDARD 20)

add_executable(SpaceLabStudio main.cpp third_party/glad/src/glad.c)

target_link_libraries(SpaceLabStudio
    app
    render
    platform
    glfw
    math
)