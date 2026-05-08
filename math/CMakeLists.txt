

add_library(math
    include/math/objects/Vectors.h
    src/Math.cpp
)

target_include_directories(math
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)