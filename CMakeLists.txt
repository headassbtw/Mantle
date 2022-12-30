cmake_minimum_required(VERSION 3.22)
project(COREtool)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMake_Modules)

add_compile_definitions(CORETOOL_VERSION_MAJOR=0)
add_compile_definitions(CORETOOL_VERSION_MINOR=0)
add_compile_definitions(CORETOOL_VERSION_PATCH=0)

include_directories(include)
include_directories(external/imgui)
include_directories(external/glfw/include)
include_directories(external/glfw/src)
include_directories(external/glew/include)
include_directories(external/tinyfiledialogs)
include_directories(external/glm)
find_package(OpenGL REQUIRED)
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
    src/*.cpp
    external/tinyfiledialogs/*.c
)
file(GLOB IM_SRC CONFIGURE_DEPENDS
    "external/imgui/*.cpp"
    "external/imgui/misc/*.cpp"
    "external/imgui/backends/imgui_impl_opengl3.cpp"
    "external/imgui/backends/imgui_impl_glfw.cpp"
)
include(generate_product_version)

set(APP_COPYRIGHT "headassbtw (C) Copyright 2022")
set(APP_NAME "COREtool")
set(APP_INFOSTRING "Some bullshit app to help read Killzone 2 .core files")
generate_product_version(
   VersionFilesOutputVariable
   NAME ${APP_NAME}
   COMMENTS ${APP_INFOSTRING}
   COMPANY_COPYRIGHT ${APP_COPYRIGHT}
   VERSION_MAJOR CORETOOL_VERSION_MAJOR
   VERSION_MINOR CORETOOL_VERSION_MINOR
   VERSION_PATCH CORETOOL_VERSION_PATCH
)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(BUILD_UTILS OFF)

add_library(ImGui STATIC ${IM_SRC})
add_subdirectory(external/glfw)
add_subdirectory(external/glew/build/cmake)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden -Wall")
if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Windows)
    set(CMAKE_EXE_LINKER_FLAGS " -static")
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Linux)
endif()

if(WIN32)
    add_executable(COREtool WIN32 ${SRC} ${VersionFilesOutputVariable})
else()
    add_executable(COREtool ${SRC})
endif()

target_link_libraries(COREtool glew_s glfw ImGui -static-libgcc -static-libstdc++ -s)
