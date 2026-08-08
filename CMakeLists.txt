cmake_minimum_required(VERSION 3.20)

if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
    cmake_policy(SET CMP0135 NEW)
endif ()

project(SchlapBot)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

option(BUILD_SC2_RENDERER "Build SC2 Renderer library" ON)
option(BUILD_FOR_LADDER "Create build for the AIArena ladder" OFF)

set(SC2_VERSION "5.0.14" CACHE STRING "Version of the target StarCraft II client")
message(STATUS "Target SC2 version: ${SC2_VERSION}")

# Use bin as the directory for all executables and binaries
set(CPP_SC2_BUILD_DIR "${PROJECT_BINARY_DIR}/bin")
set(EXECUTABLE_OUTPUT_PATH "${CPP_SC2_BUILD_DIR}")
set(LIBRARY_OUTPUT_PATH "${CPP_SC2_BUILD_DIR}")

set(build_types DEBUG RELEASE RELWITHDEBINFO)
set(output_types LIBRARY ARCHIVE RUNTIME)

foreach (build IN LISTS build_types)
    foreach (output IN LISTS output_types)
        set(CMAKE_${output}_OUTPUT_DIRECTORY_${build} "${CPP_SC2_BUILD_DIR}")
    endforeach ()
endforeach ()

set(LIBRARY_DEBUG_POSTFIX d)
set(CMAKE_DEBUG_POSTFIX ${LIBRARY_DEBUG_POSTFIX})

# Module paths for finding framework cmake files
list(APPEND CMAKE_MODULE_PATH
        "${PROJECT_SOURCE_DIR}/thirdparty/cmake"
        "${PROJECT_SOURCE_DIR}/thirdparty/civetweb"
        "${PROJECT_SOURCE_DIR}/cmake/assets")

# Build with C++20 support
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (MSVC)
    # Setup MSVC parallelized builds
    add_compile_options(/MP)

    # Use statically linked runtime
    set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>)
endif ()

# cpp-sc2 core dependency configuration

# Required dependencies that download protocols, protobuf, and build libraries
include(civetweb)
include(protobuf)
include(sc2protocol)

if (BUILD_SC2_RENDERER)
    include(SDL)
endif ()

# Compile your custom bot source folder
add_subdirectory(src)