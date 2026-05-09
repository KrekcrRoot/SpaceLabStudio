cmake_minimum_required(VERSION 4.0)
project(SpaceLabStudio)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(third_party/glad/include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(third_party/glfw)

include_directories(third_party/glm)
include_directories(third_party/stb)

add_subdirectory(render)
add_subdirectory(app)
add_subdirectory(platform)
add_subdirectory(math)
add_subdirectory(ui)


add_executable(SpaceLabStudio main.cpp third_party/glad/src/glad.c)

target_link_libraries(SpaceLabStudio
    app
    render
    platform
    glfw
    math
    ui
)

target_include_directories(SpaceLabStudio PRIVATE
    third_party/glad/include
    third_party/glm
    third_party/stb
)