set(ENGINE_RENDERER_PROJECT "Renderer")

find_package(OpenGL REQUIRED)

file(
    GLOB_RECURSE ENGINE_RENDERER_CODE_LIST
    LIST_DIRECTORIES false
    "${CMAKE_SOURCE_DIR}/src/renderer/src/*.c*"
    "${CMAKE_SOURCE_DIR}/src/renderer/include/renderer/*.h*"
    "${CMAKE_SOURCE_DIR}/src/renderer/include/renderer/*.inl"
    "${CMAKE_SOURCE_DIR}/src/renderer/shaders/*.glsl"
)

add_library(${ENGINE_RENDERER_PROJECT} STATIC ${ENGINE_RENDERER_CODE_LIST})

target_compile_features(${ENGINE_RENDERER_PROJECT} PRIVATE cxx_std_17)
target_include_directories(${ENGINE_RENDERER_PROJECT} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/logs/include
    ${CMAKE_SOURCE_DIR}/src/renderer/include
    ${CMAKE_SOURCE_DIR}/src/tools/include
    ${CMAKE_SOURCE_DIR}/src/ui/include
    ${ENGINE_EXTERNAL_INCLUDE_DIR}
)
target_link_libraries(${ENGINE_RENDERER_PROJECT} ${ENGINE_LIBS_LIST} OpenGL::GL Logs Tools UI)

foreach(CODE_FILE IN ITEMS ${ENGINE_RENDERER_CODE_LIST})
    get_filename_component(CODE_FILE_PATH "${CODE_FILE}" PATH)
    file(RELATIVE_PATH CODE_FILE_RELATIVE_PATH "${CMAKE_SOURCE_DIR}/src/renderer" "${CODE_FILE_PATH}")
    string(REPLACE "\\" "/" GROUP_PATH "${CODE_FILE_RELATIVE_PATH}")
    file(RELATIVE_PATH EXTERNAL_INCLUDE_RELATIVE_PATH "${CMAKE_SOURCE_DIR}/src/renderer" "${ENGINE_EXTERNAL_INCLUDE_DIR}/")
    string(REPLACE ${EXTERNAL_INCLUDE_RELATIVE_PATH} "" GROUP_PATH "${GROUP_PATH}")
    string(REPLACE "src" "" GROUP_PATH "${GROUP_PATH}")
    string(REPLACE "include/renderer" "" GROUP_PATH "${GROUP_PATH}")
    source_group("${GROUP_PATH}" FILES "${CODE_FILE}")
endforeach()
