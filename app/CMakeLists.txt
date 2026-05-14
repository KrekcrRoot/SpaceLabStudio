add_library(app
        Application.h
        Application.cpp
)

target_include_directories(app
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/ml
)

target_link_libraries(app PUBLIC render ui ml)