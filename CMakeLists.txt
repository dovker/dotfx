cmake_minimum_required(VERSION 3.5)

project(dotfx LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE DFX_SRC_FILES "src/*.cpp" 
                                 "src/*.h")

add_executable(DFX ${DFX_SRC_FILES})

add_compile_definitions(CLAP_USE_OPENGL CLAP_USE_OPENGL_4_5 CLAP_USE_SDL2 _CRT_SCURE_NO_WARNINGS)

add_subdirectory(../ Clap)

target_include_directories(DFX SYSTEM PUBLIC ${CLAP_WORKSPACE_DIR}/Clap/src
                                  SYSTEM PUBLIC ${CLAP_INCLUDE_DIRS})


target_link_directories(DFX PRIVATE ${CLAP_LINK_DIRS})

target_link_libraries(DFX PUBLIC Clap SDL2main bgfx SDL2-static ImGui lua-lib yaml-cpp)


