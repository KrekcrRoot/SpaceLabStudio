add_library(ml
    ImageUtils.cpp
    OnnxRecognizer.cpp
    Recognizer.cpp
)

find_library(ORT_LIB
    NAMES onnxruntime
    PATHS ${CMAKE_SOURCE_DIR}/third_party/onnxruntime/lib
    NO_DEFAULT_PATH
    REQUIRED
)

find_path(ORT_INCLUDE
    NAMES onnxruntime_cxx_api.h
    PATHS ${CMAKE_SOURCE_DIR}/third_party/onnxruntime/include
    NO_DEFAULT_PATH
    REQUIRED
)

target_include_directories(ml PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ORT_INCLUDE}
    ${CMAKE_SOURCE_DIR}/third_party/stb
    ${CMAKE_SOURCE_DIR}/third_party/json
)

target_link_libraries(ml
    ${ORT_LIB}
)