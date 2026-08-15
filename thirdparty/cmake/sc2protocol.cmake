message(STATUS "FetchContent: protocol")

# Suppress all warnings from civetweb.
if (SUPPRESS_DEPENDENCY_WARNINGS)
    add_compile_options(-w)
endif ()

FetchContent_Declare(
    s2client_proto_repo
    GIT_REPOSITORY https://github.com/Blizzard/s2client-proto.git
    GIT_TAG 7212ae512d15aa93a708e025d3ab9af4a9c4138f
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(s2client_proto_repo)

# 1. Define the library target and list the proto source files
add_library(sc2protocol
    # Use the FetchContent source directory variable for paths
    ${s2client_proto_repo_SOURCE_DIR}/s2clientprotocol/sc2api.proto
    ${s2client_proto_repo_SOURCE_DIR}/s2clientprotocol/common.proto
    ${s2client_proto_repo_SOURCE_DIR}/s2clientprotocol/data.proto
    ${s2client_proto_repo_SOURCE_DIR}/s2clientprotocol/debug.proto
    ${s2client_proto_repo_SOURCE_DIR}/s2clientprotocol/error.proto
    ${s2client_proto_repo_SOURCE_DIR}/s2clientprotocol/query.proto
    ${s2client_proto_repo_SOURCE_DIR}/s2clientprotocol/raw.proto
    ${s2client_proto_repo_SOURCE_DIR}/s2clientprotocol/score.proto
    ${s2client_proto_repo_SOURCE_DIR}/s2clientprotocol/spatial.proto
    ${s2client_proto_repo_SOURCE_DIR}/s2clientprotocol/ui.proto
)

# 2. Resolve the protoc executable BEFORE calling protobuf_generate
if (TARGET protobuf::protoc)
    set(PROTOC_CMD PROTOC_EXE protobuf::protoc)
elseif (Protobuf_PROTOC_EXECUTABLE)
    set(PROTOC_CMD PROTOC_EXE "${Protobuf_PROTOC_EXECUTABLE}")
else()
    # Fallback search if FindProtobuf missed it
    find_program(Protobuf_PROTOC_EXECUTABLE protoc REQUIRED)
    set(PROTOC_CMD PROTOC_EXE "${Protobuf_PROTOC_EXECUTABLE}")
endif()

# 3. Generate C++ headers/sources ONCE using the resolved protoc binary
protobuf_generate(
    TARGET sc2protocol
    ${PROTOC_CMD}
    IMPORT_DIRS ${s2client_proto_repo_SOURCE_DIR}
)

# 4. Target Linking & Header Directories
target_link_libraries(sc2protocol PUBLIC protobuf::libprotobuf)

target_include_directories(sc2protocol PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
)

# 5. Compiler-Specific Flags and Workarounds
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # GCC / MinGW C++20 Module Workaround:
    # GCC's module engine enforces strict linkage checks on header entity exports.
    # MSVC handles these natively inside the Global Module Fragment and does not require patching.
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/patch_headers.cmake" [=[
        file(GLOB_RECURSE PROTO_HEADERS "${HEADERS_DIR}/*.pb.h")
        foreach(HEADER ${PROTO_HEADERS})
            file(READ "${HEADER}" CONTENT)

            # Upgrade all 'constexpr' declarations to 'inline constexpr'
            # This grants external linkage required for C++20 modules while leaving
            # struct members like TableStruct::offsets (static const) untouched.
            string(REPLACE "constexpr " "inline constexpr " CONTENT "${CONTENT}")

            # Remove `inline` doubles.
            string(REPLACE "inline inline" "inline" CONTENT "${CONTENT}")
            string(REPLACE "inline explicit inline constexpr" "explicit constexpr" CONTENT "${CONTENT}")

            file(WRITE "${HEADER}" "${CONTENT}")
        endforeach()
    ]=])

    add_custom_command(
        TARGET sc2protocol POST_BUILD
        COMMAND ${CMAKE_COMMAND}
            -DHEADERS_DIR=${CMAKE_CURRENT_BINARY_DIR}/s2clientprotocol
            -P ${CMAKE_CURRENT_BINARY_DIR}/patch_headers.cmake
        COMMENT "Patching generated Protobuf headers for C++20 module compatibility..."
    )
elseif (MSVC)
    target_compile_options(sc2protocol PRIVATE /W0)
endif ()
