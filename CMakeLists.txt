cmake_minimum_required(VERSION 4.3.1)

# The exact UUID string varies by CMake version (check CMake's
# Help/dev/experimental.rst)
# VERSION 4.3.1  451f2fe2-a8a2-47c3-bc32-94786d8fc91b
# VERSION 4.4.3  f35a9ac6-8463-4d38-8eec-5d6008153e7d
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d")

option(BUILD_SC2_RENDERER "Build SC2 Renderer library" OFF)
option(BUILD_FOR_LADDER "Create build for the AIArena ladder" OFF)
option(BUILD_API_EXAMPLES "Build Examples" OFF)
option(BUILD_API_TESTS "Build Tests" OFF)
option(CACHE_DEPENDENCIES "Cache Dependencies" ON)
option(DEPENDENCY_WARNINGS "Dependency Warnings" OFF)
message(STATUS "-------------------------------------------")
message(STATUS " Configuration Summary:")
message(STATUS "     BUILD_SC2_RENDERER : ${BUILD_SC2_RENDERER}")
message(STATUS "       BUILD_FOR_LADDER : ${BUILD_FOR_LADDER}")
message(STATUS "     BUILD_API_EXAMPLES : ${BUILD_API_EXAMPLES}")
message(STATUS "        BUILD_API_TESTS : ${BUILD_API_TESTS}")
message(STATUS "     CACHE_DEPENDENCIES : ${CACHE_DEPENDENCIES}")
message(STATUS "    DEPENDENCY_WARNINGS : ${DEPENDENCY_WARNINGS}")
message(STATUS " Changeable in root CMakeLists.txt")
message(STATUS "------------------------------------------------")

project(SchlapBot LANGUAGES CXX)

#target_compile_options(my_project PRIVATE -O0 -fno-lto)

# Restrict compilation jobs to 4 parallel workers globally
#set_property(GLOBAL PROPERTY JOB_POOLS core_limit_pool=1)
#set(CMAKE_JOB_POOL_COMPILE core_limit_pool)

if(CACHE_DEPENDENCIES)
	find_program(SCCACHE_PROGRAM sccache)
	if(SCCACHE_PROGRAM) # Compiler caching tool
		message(STATUS "${SCCACHE_PROGRAM} Found")
		set(SCCACHE_CONF)
		set(CMAKE_CXX_COMPILER_LAUNCHER "${SCCACHE_PROGRAM}")
		set(CMAKE_C_COMPILER_LAUNCHER "${SCCACHE_PROGRAM}")
	endif()
endif()

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
  cmake_policy(SET CMP0135 NEW)
endif()

# Skip generating proto files with Protobuf compiler and use prebuilt files Will
# still build Protobuf as libprotobuf is required for linking
option(WSL2_CROSS_COMPILE "Building on WSL2 for Windows" OFF)

# Downstream projects including cpp-sc2 as a dependency must set toolchain the
# toolchain file
if(DEFINED CMAKE_TOOLCHAIN_FILE)
  message(DEBUG "Toolchain file already set to ${CMAKE_TOOLCHAIN_FILE}")
elseif(WSL2_CROSS_COMPILE)
  set(CMAKE_TOOLCHAIN_FILE cmake/toolchain/x86-64-w64-mingw32.cmake)
endif()

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

set(SC2_VERSION
    "5.0.14"
    CACHE STRING "Version of the target StarCraft II client")
message(STATUS "Target SC2 version: ${SC2_VERSION}")

# Use bin as the directory for all executables. This will make protoc easy to
# find.
set(CPP_SC2_BUILD_DIR "${PROJECT_BINARY_DIR}/bin")
set(EXECUTABLE_OUTPUT_PATH "${CPP_SC2_BUILD_DIR}")
set(LIBRARY_OUTPUT_PATH "${CPP_SC2_BUILD_DIR}")

# Windows builds subdirectories Debug/Release. These variables will overwrite
# that and put binaries in bin.
set(build_types DEBUG RELEASE RELWITHDEBINFO)
set(output_types LIBRARY ARCHIVE RUNTIME)

foreach(build IN LISTS build_types)
  foreach(output IN LISTS output_types)
    set(CMAKE_${output}_OUTPUT_DIRECTORY_${build} "${CPP_SC2_BUILD_DIR}")
  endforeach()
endforeach()

# All libraries built with debug should be the same postfix
set(LIBRARY_DEBUG_POSTFIX d)
set(CMAKE_DEBUG_POSTFIX ${LIBRARY_DEBUG_POSTFIX})

# External subprojects
list(
    APPEND   CMAKE_MODULE_PATH
  "${PROJECT_SOURCE_DIR}/thirdparty/cmake"
  "${PROJECT_SOURCE_DIR}/thirdparty/civetweb"
  "${PROJECT_SOURCE_DIR}/thirdparty/protobuf"
  "${PROJECT_SOURCE_DIR}/cmake/assets")

# Build with c++20 support.
set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
set(ABSL_CXX_STANDARD 20)
set(ABSL_USE_CXX17 1) # Forces ABSL_INTERNAL_INLINE_CONSTEXPR to use 'inline'

# Cross-platform compiler warnings and flags REUSABLE WARNING TARGET
add_library(project_warnings INTERFACE)
target_compile_options(
  project_warnings
  INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX->
            $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>)

# Allow creating filters for projects in visual studio.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Only apply -W flags to GCC/Clang
    add_compile_options(-Wno-unused-function)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        # For deep code debugging
        add_compile_options(-ggdb3 -Og -fno-omit-frame-pointer)

        # For capturing compiler crash traces
#        add_compile_options(-save-temps=obj -freport-bug)
    endif()
elseif(MSVC)
    add_compile_options(
            /Zc:preprocessor # Mandatory: standard-conforming preprocessor
            # for GMF macros
            /bigobj # Prevents section count overflow from template-heavy protos
    )
    set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>
    )# Use statically linked runtime
    set(CMAKE_MFC_FLAG 0)
    # Tell CMake to use /Z7 (Embedded) instead of /Zi (ProgramDatabase)
    # This is required for sccache to work correctly with MSVC debug builds.
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT Embedded)
endif()

if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE FALSE)
elseif(APPLE)
  find_library(COREFOUNDATION_FRAMEWORK CoreFoundation) # Transitive dependency
elseif(UNIX)
  find_package(Threads REQUIRED) # Transitive dependency
endif()

# External subproject dependencies
include(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/protobuf/protobuf.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/cmake/sc2protocol.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/civetweb/civetweb.cmake)
if(BUILD_SC2_RENDERER)
  include(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/cmake/SDL.cmake)
endif()
if(WSL2_CROSS_COMPILE)
  include(protos)
endif()

# cpp-sc2 libraries
add_subdirectory(src)
