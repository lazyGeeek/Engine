set(ENGINE_LOGS_PROJECT "Logs")

file(
    GLOB_RECURSE ENGINE_LOGS_CODE_LIST
    LIST_DIRECTORIES false
    "${CMAKE_SOURCE_DIR}/src/logs/src/*.c*"
    "${CMAKE_SOURCE_DIR}/src/logs/include/logs/*.h*"
    "${CMAKE_SOURCE_DIR}/src/logs/include/logs/*.inl"
)

add_library(${ENGINE_LOGS_PROJECT} STATIC ${ENGINE_LOGS_CODE_LIST})

target_compile_features(${ENGINE_LOGS_PROJECT} PRIVATE cxx_std_17)
target_include_directories(${ENGINE_LOGS_PROJECT} PRIVATE 
    ${CMAKE_SOURCE_DIR}/src/logs/include
    ${CMAKE_SOURCE_DIR}/src/tools/include
    ${CMAKE_SOURCE_DIR}/src/ui/include
    ${ENGINE_EXTERNAL_INCLUDE_DIR}
    ${ENGINE_EXTERNAL_INCLUDE_DIR}/imgui
)
target_link_libraries(${ENGINE_LOGS_PROJECT} ${ENGINE_LIBS_LIST} Tools UI)

foreach(CODE_FILE IN ITEMS ${ENGINE_LOGS_CODE_LIST})
    get_filename_component(CODE_FILE_PATH "${CODE_FILE}" PATH)
    file(RELATIVE_PATH CODE_FILE_RELATIVE_PATH "${CMAKE_SOURCE_DIR}/src/logs" "${CODE_FILE_PATH}")
    string(REPLACE "\\" "/" GROUP_PATH "${CODE_FILE_RELATIVE_PATH}")
    file(RELATIVE_PATH EXTERNAL_INCLUDE_RELATIVE_PATH "${CMAKE_SOURCE_DIR}/src/logs" "${ENGINE_EXTERNAL_INCLUDE_DIR}/")
    string(REPLACE ${EXTERNAL_INCLUDE_RELATIVE_PATH} "" GROUP_PATH "${GROUP_PATH}")
    string(REPLACE "src" "" GROUP_PATH "${GROUP_PATH}")
    string(REPLACE "include/logs" "" GROUP_PATH "${GROUP_PATH}")
    source_group("${GROUP_PATH}" FILES "${CODE_FILE}")
endforeach()
