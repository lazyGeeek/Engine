set(ENGINE_PROJECT "Engine")

file(
    GLOB_RECURSE ENGINE_CODE_LIST
    LIST_DIRECTORIES false
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/engine/*.h*"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/engine/*.inl"
)

add_executable(${ENGINE_PROJECT} ${ENGINE_CODE_LIST})

target_compile_features(${ENGINE_PROJECT} PRIVATE cxx_std_20)
target_include_directories(${ENGINE_PROJECT} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Utils/include
    ${CMAKE_SOURCE_DIR}/Renderer/include
    ${CMAKE_SOURCE_DIR}/Window/include
    ${CMAKE_SOURCE_DIR}/Window/thirdparty/include)
target_link_libraries(${ENGINE_PROJECT} Utils Renderer Window)

foreach(ENGINE_FILE IN ITEMS ${ENGINE_CODE_LIST})
    get_filename_component(ENGINE_FILE_PATH "${ENGINE_FILE}" PATH)
    file(RELATIVE_PATH ENGINE_FILE_RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" "${ENGINE_FILE_PATH}")
    string(REPLACE "\\" "/" GROUP_PATH "${ENGINE_FILE_RELATIVE_PATH}")
    file(RELATIVE_PATH EXTERNAL_INCLUDE_RELATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/include")
    string(REPLACE ${EXTERNAL_INCLUDE_RELATIVE_PATH} "" GROUP_PATH "${GROUP_PATH}")
    string(REPLACE "src" "" GROUP_PATH "${GROUP_PATH}")
    string(REPLACE "include/engine" "" GROUP_PATH "${GROUP_PATH}")
    source_group("${GROUP_PATH}" FILES "${ENGINE_FILE}")
endforeach()
