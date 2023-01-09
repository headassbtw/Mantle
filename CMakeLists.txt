cmake_minimum_required(VERSION 3.22)
project(Mantle)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMake_Modules)

set(MANTLE_VERSION_MAJOR 0)
set(MANTLE_VERSION_MINOR 0)
set(MANTLE_VERSION_PATCH 0)

add_compile_definitions(MANTLE_VERSION_MAJOR=${MANTLE_VERSION_MAJOR})
add_compile_definitions(MANTLE_VERSION_MINOR=${MANTLE_VERSION_MINOR})
add_compile_definitions(MANTLE_VERSION_PATCH=${MANTLE_VERSION_PATCH})

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

set(APP_COPYRIGHT "headassbtw (C) Copyright 2023")
set(APP_NAME "Mantle")
set(APP_INFOSTRING "Some bullshit app to help read Killzone 2 .core files")
set(APP_VERSIONSTRING "${MANTLE_VERSION_MAJOR}.${MANTLE_VERSION_MINOR}.${MANTLE_VERSION_PATCH}")
generate_product_version(
   VersionFilesOutputVariable
   NAME ${APP_NAME}
   COMMENTS ${APP_INFOSTRING}
   COMPANY_COPYRIGHT ${APP_COPYRIGHT}
   VERSION_MAJOR MANTLE_VERSION_MAJOR
   VERSION_MINOR MANTLE_VERSION_MINOR
   VERSION_PATCH MANTLE_VERSION_PATCH
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
elseif(APPLE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Mac)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Linux)
endif()

if(WIN32)
    add_executable(Mantle WIN32 ${SRC} ${VersionFilesOutputVariable})
elseif(APPLE)
    set(MANTLE_ICON ${CMAKE_CURRENT_SOURCE_DIR}/gfx/product.icns)
    set_source_files_properties(${MANTLE_ICON} PROPERTIES
       MACOSX_PACKAGE_LOCATION "Resources")
    set(MACOSX_BUNDLE_ICON_FILE product.icns)
    set(MACOSX_BUNDLE_BUNDLE_NAME ${APP_NAME})
    set(MACOSX_BUNDLE_COPYRIGHT ${APP_COPYRIGHT})
    set(MACOSX_BUNDLE_INFO_STRING ${APP_INFOSTRING})
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${APP_VERSIONSTRING})
    set(MACOSX_BUNDLE_BUNDLE_VERSION ${APP_VERSIONSTRING})
    add_executable(Mantle MACOSX_BUNDLE ${SRC} ${MANTLE_ICON})
else()
    add_executable(Mantle ${SRC})
endif()

if(APPLE)
    target_link_libraries(Mantle ImGui glew_s glfw "-framework Cocoa"
                                       "-framework IOKit"
                                       "-framework CoreFoundation")
else()
    target_link_libraries(Mantle ImGui glew_s glfw -static-libgcc -static-libstdc++ -s)
endif()
