set(ENGINE_ENGINE_PROJECT "Engine")

file(
    GLOB_RECURSE ENGINE_ENGINE_CODE_LIST
    LIST_DIRECTORIES false
    "${CMAKE_SOURCE_DIR}/src/tools/src/*.c*"
    "${CMAKE_SOURCE_DIR}/src/tools/include/tools/*.h*"
    "${CMAKE_SOURCE_DIR}/src/logs/src/*.c*"
    "${CMAKE_SOURCE_DIR}/src/logs/include/logs/*.h*"
    "${CMAKE_SOURCE_DIR}/src/engine/src/*.c*"
    "${CMAKE_SOURCE_DIR}/src/engine/include/engine/*.h*"
    "${CMAKE_SOURCE_DIR}/src/engine/include/engine/*.inl"
)

add_executable(${ENGINE_ENGINE_PROJECT} ${ENGINE_ENGINE_CODE_LIST})

target_compile_features(${ENGINE_ENGINE_PROJECT} PRIVATE cxx_std_17)
target_include_directories(${ENGINE_ENGINE_PROJECT} PRIVATE 
    ${CMAKE_SOURCE_DIR}/src/engine/include
    # ${CMAKE_SOURCE_DIR}/src/hardware_info/include
    ${CMAKE_SOURCE_DIR}/src/logs/include
    # ${CMAKE_SOURCE_DIR}/src/renderer/include
    ${CMAKE_SOURCE_DIR}/src/tools/include
    # ${CMAKE_SOURCE_DIR}/src/ui/include
    ${CMAKE_SOURCE_DIR}/src/windows/include
    ${ENGINE_EXTERNAL_INCLUDE_DIR}
    # ${ENGINE_EXTERNAL_INCLUDE_DIR}/imgui
)
target_link_libraries(${ENGINE_ENGINE_PROJECT} Windows) # HardwareInfo Logs Renderer Tools UI Windows)

foreach(CODE_FILE IN ITEMS ${ENGINE_ENGINE_CODE_LIST})
    get_filename_component(CODE_FILE_PATH "${CODE_FILE}" PATH)
    file(RELATIVE_PATH CODE_FILE_RELATIVE_PATH "${CMAKE_SOURCE_DIR}/src/engine" "${CODE_FILE_PATH}")
    string(REPLACE "\\" "/" GROUP_PATH "${CODE_FILE_RELATIVE_PATH}")
    file(RELATIVE_PATH EXTERNAL_INCLUDE_RELATIVE_PATH "${CMAKE_SOURCE_DIR}/src/engine" "${ENGINE_EXTERNAL_INCLUDE_DIR}/")
    string(REPLACE ${EXTERNAL_INCLUDE_RELATIVE_PATH} "" GROUP_PATH "${GROUP_PATH}")
    string(REPLACE "src" "" GROUP_PATH "${GROUP_PATH}")
    string(REPLACE "include/engine" "" GROUP_PATH "${GROUP_PATH}")
    source_group("${GROUP_PATH}" FILES "${CODE_FILE}")
endforeach()

add_custom_command(TARGET ${ENGINE_ENGINE_PROJECT} PRE_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_SOURCE_DIR}/thirdparty/engine/Configs $<TARGET_FILE_DIR:${ENGINE_ENGINE_PROJECT}>/Configs)

add_custom_command(TARGET ${ENGINE_ENGINE_PROJECT} PRE_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_SOURCE_DIR}/thirdparty/engine/Models $<TARGET_FILE_DIR:${ENGINE_ENGINE_PROJECT}>/Models)

# add_custom_command(TARGET ${ENGINE_ENGINE_PROJECT} PRE_BUILD
#                     COMMAND ${CMAKE_COMMAND} -E copy_directory
#                         ${CMAKE_SOURCE_DIR}/src/renderer/shaders $<TARGET_FILE_DIR:${ENGINE_ENGINE_PROJECT}>/Shaders)
