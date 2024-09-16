set(ENGINE_UI_PROJECT "UI")

file(
    GLOB_RECURSE ENGINE_UI_CODE_LIST
    LIST_DIRECTORIES false
    "${CMAKE_SOURCE_DIR}/src/ui/src/*.c*"
    "${CMAKE_SOURCE_DIR}/src/ui/include/ui/*.h*"
    "${CMAKE_SOURCE_DIR}/src/ui/include/ui/*.inl"
    "${ENGINE_EXTERNAL_INCLUDE_DIR}/imgui/backends/imgui_impl_opengl3.cpp"
    "${ENGINE_EXTERNAL_INCLUDE_DIR}/imgui/backends/imgui_impl_opengl3.h"
    "${ENGINE_EXTERNAL_INCLUDE_DIR}/imgui/backends/imgui_impl_glfw.cpp"
    "${ENGINE_EXTERNAL_INCLUDE_DIR}/imgui/backends/imgui_impl_glfw.h"
    "${ENGINE_EXTERNAL_INCLUDE_DIR}/imgui/imgui.cpp"
    "${ENGINE_EXTERNAL_INCLUDE_DIR}/imgui/imgui.h"
    "${ENGINE_EXTERNAL_INCLUDE_DIR}/imgui/imgui_draw.cpp"
    "${ENGINE_EXTERNAL_INCLUDE_DIR}/imgui/imgui_internal.h"
    "${ENGINE_EXTERNAL_INCLUDE_DIR}/imgui/imgui_widgets.cpp"
    "${ENGINE_EXTERNAL_INCLUDE_DIR}/imgui/imgui_tables.cpp"
)

add_library(${ENGINE_UI_PROJECT} STATIC ${ENGINE_UI_CODE_LIST})

target_compile_features(${ENGINE_UI_PROJECT} PRIVATE cxx_std_17)
target_include_directories(${ENGINE_UI_PROJECT} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/tools/include
    ${CMAKE_SOURCE_DIR}/src/ui/include
    ${CMAKE_SOURCE_DIR}/src/windows/include
    ${ENGINE_EXTERNAL_INCLUDE_DIR}
    ${ENGINE_EXTERNAL_INCLUDE_DIR}/imgui
)
target_link_libraries(${ENGINE_UI_PROJECT} ${ENGINE_LIBS_LIST} Tools Windows)

foreach(CODE_FILE IN ITEMS ${ENGINE_UI_CODE_LIST})
    get_filename_component(CODE_FILE_PATH "${CODE_FILE}" PATH)
    file(RELATIVE_PATH CODE_FILE_RELATIVE_PATH "${CMAKE_SOURCE_DIR}/src/ui" "${CODE_FILE_PATH}")
    string(REPLACE "\\" "/" GROUP_PATH "${CODE_FILE_RELATIVE_PATH}")
    file(RELATIVE_PATH EXTERNAL_INCLUDE_RELATIVE_PATH "${CMAKE_SOURCE_DIR}/src/ui" "${ENGINE_EXTERNAL_INCLUDE_DIR}/")
    string(REPLACE ${EXTERNAL_INCLUDE_RELATIVE_PATH} "" GROUP_PATH "${GROUP_PATH}")
    string(REPLACE "src" "" GROUP_PATH "${GROUP_PATH}")
    string(REPLACE "include/ui" "" GROUP_PATH "${GROUP_PATH}")
    source_group("${GROUP_PATH}" FILES "${CODE_FILE}")
endforeach()
