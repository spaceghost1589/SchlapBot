cmake_minimum_required(VERSION 4.3.1)

#region Custom CMake Settings
option(BUILD_SC2_RENDERER "Build SC2 Renderer library" OFF)
option(BUILD_FOR_LADDER "Create build for the AIArena ladder" OFF)
option(BUILD_API_EXAMPLES "Build Examples" OFF)
option(BUILD_API_TESTS "Build Tests" OFF)
option(SCCACHE "Cache Dependencies" OFF)
option(DEPENDENCY_WARNINGS "Dependency Warnings" OFF)
option(CMAKE_DEBUG "CMake Debug" OFF)
message(STATUS "--------------------------------------------------------------")
message(STATUS "----- Configuration Summary :")
message(STATUS "-----    BUILD_SC2_RENDERER : ${BUILD_SC2_RENDERER}")
message(STATUS "-----      BUILD_FOR_LADDER : ${BUILD_FOR_LADDER}")
message(STATUS "-----    BUILD_API_EXAMPLES : ${BUILD_API_EXAMPLES}")
message(STATUS "-----       BUILD_API_TESTS : ${BUILD_API_TESTS}")
message(STATUS "-----    CACHE_DEPENDENCIES : ${SCCACHE}")
message(STATUS "-----   DEPENDENCY_WARNINGS : ${DEPENDENCY_WARNINGS}")
message(STATUS "-----           CMAKE_DEBUG : ${CMAKE_DEBUG}")
message(STATUS "----- Changeable in root CMakeLists.txt")
message(STATUS "--------------------------------------------------------------")
#endregion

#region Simplified Compiler Bools
set(GNU_ OFF)
set(CLANG_ OFF)
# Check compiler and set state accordingly
# "MSVC" is natively supported.
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(GNU_ ON)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CLANG_ ON)
endif ()
# Define the cache options using those defaults
option(GNU "GNU / GCC / MinGW" ${GNU_})
option(CLANG "Clang" ${CLANG_})
#endregion

#region Compiler No Warnings Flags
if (NOT DEPENDENCY_WARNINGS)
    if (MSVC)
        set(_no_warn_flag " /W0")
    else () # GNU or Clang
        set(_no_warn_flag " -w")
    endif ()
else ()
    set(_no_warn_flag "")
endif ()
#endregion

#region CMake UUID Version String
#( check CMake's Help / dev / experimental.rst )
#VERSION 4.3.1 451F2Fe2-a8a2-47C3-bc32-94786D8FC91B
#VERSION 4.4.3 f35a9ac6-8463-4D38-8eeC-5D6008153e7d
#set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d" CACHE INTERNAL "Experimental import std")
#endregion
option(CMAKE_DEBUG "CMake Debug" OFF)
message(STATUS "--------------------------------------------------------------")
message(STATUS "----- Configuration Summary :")
message(STATUS "-----    BUILD_SC2_RENDERER : ${BUILD_SC2_RENDERER}")
message(STATUS "-----      BUILD_FOR_LADDER : ${BUILD_FOR_LADDER}")
message(STATUS "-----    BUILD_API_EXAMPLES : ${BUILD_API_EXAMPLES}")
message(STATUS "-----       BUILD_API_TESTS : ${BUILD_API_TESTS}")
message(STATUS "-----    CACHE_DEPENDENCIES : ${SCCACHE}")
message(STATUS "-----   DEPENDENCY_WARNINGS : ${DEPENDENCY_WARNINGS}")
message(STATUS "-----           CMAKE_DEBUG : ${CMAKE_DEBUG}")
message(STATUS "----- Changeable in root CMakeLists.txt")
message(STATUS "--------------------------------------------------------------")
#endregion

#region Simplified Compiler Bools
set(GNU_ OFF)
set(CLANG_ OFF)
# Check compiler and set state accordingly
# MSVC is natively supported.
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(GNU_ ON)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(CLANG_ ON)
endif()
# Define the cache options using those defaults
option(GNU "GNU / GCC / MinGW" ${GNU_})
option(CLANG "Clang" ${CLANG_})
#endregion

#region Compiler No Warnings Flags
if(NOT DEPENDENCY_WARNINGS)
  if(MSVC)
    set(_no_warn_flag " /W0")
  else() # GNU or Clang
    set(_no_warn_flag " -w")
  endif()
else()
  set(_no_warn_flag "")
endif()
#endregion

#region CMake UUID Version String
#( check CMake's Help / dev / experimental.rst )
#VERSION 4.3.1 451F2Fe2-a8a2-47C3-bc32-94786D8FC91B
#VERSION 4.4.3 f35a9ac6-8463-4D38-8eeC-5D6008153e7d
#set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d" CACHE INTERNAL "Experimental import std")
#endregion

project(SchlapBot LANGUAGES CXX)

#Expose source and binary directories globally
include_directories(
        ${CMAKE_SOURCE_DIR} # <root> folder
        ${PROJECT_BINARY_DIR} # <root>/build/<Preset_Name>
)

cmake_policy(SET CMP0135 NEW)

#Restrict compilation jobs to #N parallel workers globally
#set_property( GLOBAL PROPERTY JOB_POOLS core_limit_pool = 1 )
#set( CMAKE_JOB_POOL_COMPILE core_limit_pool )

#region SCCACHE: Compiler Caching Tool
if (SCCACHE)
    # Compiler caching tool
    find_program(SCCACHE_PROGRAM sccache)
    if (${SCCACHE_PROGRAM})
        message(STATUS "===== ${SCCACHE_PROGRAM} Found")

        # Required for MSVC: Forces /Z7 (Embedded) instead of /Zi (Program Database)
        set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT Embedded)
        # Allow /Z7 to function with sccache.
        cmake_policy(SET CMP0141 NEW)
        # /Z7 Embeds the debug symbols directly into .obj files,
        # allowing sccache to cache and retrieve the object files independently without file-locking conflicts.

        set(CMAKE_CXX_COMPILER_LAUNCHER "${SCCACHE_PROGRAM}")
        set(CMAKE_C_COMPILER_LAUNCHER "${SCCACHE_PROGRAM}")
    else ()
        message(STATUS "Error: ${SCCACHE_PROGRAM} Not Found")
    endif ()
endif ()
#endregion

#Skip generating proto files with Protobuf compiler and use prebuilt files Will
#still build Protobuf as libprotobuf is required for linking
option(WSL2_CROSS_COMPILE "Building on WSL2 for Windows" OFF)

# Downstream projects including cpp-sc2 as a dependency must set toolchain the
# toolchain file
if (DEFINED CMAKE_TOOLCHAIN_FILE)
    message(DEBUG "===== Toolchain file already set to ${CMAKE_TOOLCHAIN_FILE}")
elseif (WSL2_CROSS_COMPILE)
    set(CMAKE_TOOLCHAIN_FILE cmake/toolchain/x86-64-w64-mingw32.cmake)
endif ()

#region Load FetchContent CMake Module
include(FetchContent)
if (NOT CMAKE_DEBUG)
    set(FETCHCONTENT_QUIET FALSE)
endif ()
#endregion

set(SC2_VERSION
        "5.0.14"
        CACHE STRING "Version of the target StarCraft II client")
message(STATUS "===== Target SC2 version: ${SC2_VERSION}")

#region Executable Directory
# Use bin as the directory for all executables.
# This will make protoc easy to find.
set(CPP_SC2_BUILD_DIR "${PROJECT_BINARY_DIR}/bin")
set(EXECUTABLE_OUTPUT_PATH "${CPP_SC2_BUILD_DIR}")
set(LIBRARY_OUTPUT_PATH "${CPP_SC2_BUILD_DIR}")
#endregion

# Windows builds subdirectories Debug/Release. These variables will overwrite
# that and put binaries in bin.
set(build_types DEBUG RELEASE RELWITHDEBINFO)
set(output_types LIBRARY ARCHIVE RUNTIME)


foreach (build IN LISTS build_types)
    foreach (output IN LISTS output_types)
        set(CMAKE_${output}_OUTPUT_DIRECTORY_${build} "${CPP_SC2_BUILD_DIR}")
    endforeach ()
endforeach ()

#region Library Debug Postfix
# All libraries built with debug should be the same postfix
set(LIBRARY_DEBUG_POSTFIX d)
set(CMAKE_DEBUG_POSTFIX ${LIBRARY_DEBUG_POSTFIX})
#endregion

# External subprojects
list(
        APPEND CMAKE_MODULE_PATH
        "${PROJECT_SOURCE_DIR}/thirdparty/civetweb"
        "${PROJECT_SOURCE_DIR}/thirdparty/protobuf"
        "${PROJECT_SOURCE_DIR}/thirdparty/sc2protocol"
        "${PROJECT_SOURCE_DIR}/thirdparty/SDL"
)


#region CXX Build Versioning
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(ABSL_CXX_STANDARD 23)
# Forces ABSL_INTERNAL_INLINE_CONSTEXPR to use 'inline'
set(ABSL_USE_CXX17 1)
#endregion

# Cross-platform compiler warnings and flags REUSABLE WARNING TARGET
add_library(project_warnings INTERFACE)
target_compile_options(
        project_warnings
        INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX->
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>)

#Allow creating filters for projects in visual studio.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


if (GNU OR CLANG)
    #Only apply - W flags to GNU / Clang
    add_compile_options(
            -Wno-unused-function
            -fsanitize=address
            -fno-omit-frame-pointer
    )
    add_link_options(-fsanitize=address)
    if (GNU)
        #For deep code debugging
        add_compile_options(-ggdb3)
    endif ()
elseif (MSVC)
    # https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category?view=msvc-170
    add_compile_options(
            # /fsanitize=address
            /Zc:preprocessor # Mandatory: standard-conforming preprocessor
            # for GMF macros
            /bigobj # Prevents section count overflow from template-heavy protos
    )
    set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>)
    # Use statically linked runtime
    set(CMAKE_MFC_FLAG 0)
    if (CMAKE_DEBUG)
        # Debidding timing/trace flag
        # /Bt (Standard) or Bt+ (Verbose)
        add_compile_options(/Bt)
    endif ()
endif ()


if (WIN32)
    set(CMAKE_WIN32_EXECUTABLE FALSE)
elseif (APPLE)
    find_library(COREFOUNDATION_FRAMEWORK CoreFoundation) # Transitive dependency
elseif (UNIX)
    find_package(Threads REQUIRED) # Transitive dependency
endif ()

#region External Subproject Dependencies
include(${CMAKE_SOURCE_DIR}/thirdparty/civetweb/civetweb.cmake)
include(${CMAKE_SOURCE_DIR}/thirdparty/protobuf/protobuf.cmake)
include(${CMAKE_SOURCE_DIR}/thirdparty/sc2protocol/sc2protocol.cmake)
if (BUILD_SC2_RENDERER)
    include(${CMAKE_SOURCE_DIR}/thirdparty/SDL/SDL.cmake)
endif ()

if (WSL2_CROSS_COMPILE)
    include(protos)
endif ()
#endregion

# cpp-sc2 libraries
add_subdirectory(src)
