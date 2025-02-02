set(ENGINE_HARDWARE_INFO_PROJECT "HardwareInfo")

file(
    GLOB_RECURSE ENGINE_HARDWARE_INFO_CODE_LIST
    LIST_DIRECTORIES false
    "${CMAKE_SOURCE_DIR}/src/hardware_info/src/*.c*"
    "${CMAKE_SOURCE_DIR}/src/hardware_info/include/hardware_info/*.h*"
    "${CMAKE_SOURCE_DIR}/src/hardware_info/include/hardware_info/*.inl"
)

add_library(${ENGINE_HARDWARE_INFO_PROJECT} STATIC ${ENGINE_HARDWARE_INFO_CODE_LIST})

target_compile_features(${ENGINE_HARDWARE_INFO_PROJECT} PRIVATE cxx_std_17)
target_include_directories(${ENGINE_HARDWARE_INFO_PROJECT} PRIVATE 
    ${CMAKE_SOURCE_DIR}/src/hardware_info/include
    ${CMAKE_SOURCE_DIR}/src/logs/include
    ${CMAKE_SOURCE_DIR}/src/tools/include
    ${CMAKE_SOURCE_DIR}/src/ui/include
    ${ENGINE_EXTERNAL_INCLUDE_DIR}
    ${ENGINE_EXTERNAL_INCLUDE_DIR}/imgui
)
target_link_libraries(${ENGINE_HARDWARE_INFO_PROJECT} ${ENGINE_LIBS_LIST} Logs Tools UI)

foreach(CODE_FILE IN ITEMS ${ENGINE_HARDWARE_INFO_CODE_LIST})
    get_filename_component(CODE_FILE_PATH "${CODE_FILE}" PATH)
    file(RELATIVE_PATH CODE_FILE_RELATIVE_PATH "${CMAKE_SOURCE_DIR}/src/hardware_info" "${CODE_FILE_PATH}")
    string(REPLACE "\\" "/" GROUP_PATH "${CODE_FILE_RELATIVE_PATH}")
    file(RELATIVE_PATH EXTERNAL_INCLUDE_RELATIVE_PATH "${CMAKE_SOURCE_DIR}/src/hardware_info" "${ENGINE_EXTERNAL_INCLUDE_DIR}/")
    string(REPLACE ${EXTERNAL_INCLUDE_RELATIVE_PATH} "" GROUP_PATH "${GROUP_PATH}")
    string(REPLACE "src" "" GROUP_PATH "${GROUP_PATH}")
    string(REPLACE "include/hardware_info" "" GROUP_PATH "${GROUP_PATH}")
    source_group("${GROUP_PATH}" FILES "${CODE_FILE}")
endforeach()
