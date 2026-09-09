set(CMAKE_POLICY_DEFAULT_CMP0141 NEW)

#find_package(Protobuf QUIET)

message(STATUS "===== FetchContent: protobuf")

#find_package(Protobuf REQUIRED)
include(FetchContent)

# Use the protoc binary path if set by CMakePresets, otherwise fallback to thirdparty/protoc
#if(NOT Protobuf_PROTOC_EXECUTABLE)
#  set(Protobuf_PROTOC_EXECUTABLE "../protoc/bin/protoc.exe" CACHE FILEPATH "Path to protoc binary")
#endif()

set(protobuf_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(protobuf_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(PROTOBUF_GIT_TAG "v35.1")
#region FetchContent_Declare
FetchContent_Declare(
    protobuf
    GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
    GIT_TAG ${PROTOBUF_GIT_TAG}
    GIT_PROGRESS TRUE
    UPDATE_DISCONNECTED TRUE
    PATCH_COMMAND git apply "${CMAKE_CURRENT_LIST_DIR}/protobuf_cxx_module_fix_v35.1.patch"
    )
#endregion


#region Protobuf & Absl Compilation Warning Suppression
set(_saved_c_flags "${CMAKE_C_FLAGS}")
set(_saved_cxx_flags "${CMAKE_CXX_FLAGS}")
# compiler _no_warn_flag predetermined in root.
string(APPEND CMAKE_C_FLAGS "${_no_warn_flag}")
string(APPEND CMAKE_CXX_FLAGS "${_no_warn_flag}")
# protobuf AND absl get built inside this call.
FetchContent_MakeAvailable(protobuf)
# Set saved C/CXX flags back to their original values.
set(CMAKE_C_FLAGS "${_saved_c_flags}")
set(CMAKE_CXX_FLAGS "${_saved_cxx_flags}")
#endregion

set(protobuf_targets libprotobuf libprotobuf-lite libprotoc protoc)

# Ensure target alias exists for sc2protocol.cmake
if(NOT TARGET protobuf::libprotobuf AND TARGET libprotobuf)
  add_library(protobuf::libprotobuf ALIAS libprotobuf)
endif()

# CRITICAL: Load CMake's built-in Protobuf module to define `protobuf_generate`
