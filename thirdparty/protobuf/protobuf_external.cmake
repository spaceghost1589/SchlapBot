include(ExternalProject)

set(PROTOBUF_INSTALL_DIR "${CMAKE_SOURCE_DIR}/prebuilt/protobuf")

message(STATUS "===== Building: protobuf.exe (external)")

set(protobuf_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(protobuf_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Combine current project flags with your warning suppression flag
set(EXTERNAL_C_FLAGS "${CMAKE_C_FLAGS} ${_no_warn_flag}")
set(EXTERNAL_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${_no_warn_flag}")


ExternalProject_Add(protobuf_external
    GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
    GIT_TAG v35.1
    GIT_PROGRESS TRUE
    UPDATE_DISCONNECTED TRUE
    PATCH_COMMAND git apply "${CMAKE_CURRENT_LIST_DIR}/protobuf_cxx_module_fix_v35.1.patch"
    CMAKE_ARGS
    -DCMAKE_POLICY_DEFAULT_CMP0141=NEW
    -Dprotobuf_BUILD_TESTS=OFF
    -Dprotobuf_BUILD_EXAMPLES=OFF
    -DCMAKE_INSTALL_PREFIX=${PROTOBUF_INSTALL_DIR}
    -DCMAKE_C_FLAGS=${EXTERNAL_C_FLAGS}
    -DCMAKE_CXX_FLAGS=${EXTERNAL_CXX_FLAGS}
    )
