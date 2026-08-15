set(CMAKE_POLICY_DEFAULT_CMP0141 NEW)

message(STATUS "FetchContent: protobuf")

include(FetchContent)

# Use the protoc binary path if set by CMakePresets, otherwise fallback to thirdparty/protoc
if (NOT Protobuf_PROTOC_EXECUTABLE)
    set(Protobuf_PROTOC_EXECUTABLE "../protoc/bin/protoc.exe" CACHE FILEPATH "Path to protoc binary")
endif()

set(protobuf_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(protobuf_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    protobuf
    GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
#    GIT_TAG v33.0
    GIT_TAG v35.1
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(protobuf)

message(STATUS "[SchlapBot] Copying custom protobuf CXX_Module_Patch...")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/protobuf/cxx_module_patch/_deps/"
     DESTINATION "${CMAKE_BINARY_DIR}/_deps/")

set(protobuf_targets libprotobuf libprotobuf-lite libprotoc protoc)

# Ensure target alias exists for sc2protocol.cmake
if (NOT TARGET protobuf::libprotobuf AND TARGET libprotobuf)
    add_library(protobuf::libprotobuf ALIAS libprotobuf)
endif()

# CRITICAL: Load CMake's built-in Protobuf module to define `protobuf_generate`
include(FindProtobuf)

foreach (target IN LISTS protobuf_targets)
    if (TARGET ${target})
        set_target_properties(${target} PROPERTIES FOLDER contrib)
    endif ()

    if (MSVC)
        target_compile_options(${target} PRIVATE /W0)
    endif ()
endforeach ()
