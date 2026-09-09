set(Protobuf_PROTOC_EXECUTABLE "${CMAKE_SOURCE_DIR}/prebuilt/protobuf/bin/protoc.exe")

#region Define imported protoc target
add_executable(protobuf::protoc IMPORTED)
set_target_properties(protobuf::protoc PROPERTIES
    IMPORTED_LOCATION "${Protobuf_PROTOC_EXECUTABLE}"
    )
#endregion

#region Define imported libprotobuf target so configure-time linking succeeds
add_library(protobuf::libprotobuf STATIC IMPORTED)
set_target_properties(protobuf::libprotobuf PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/prebuilt/protobuf/lib/libprotobuf.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/prebuilt/protobuf/include"
    )
#endregion


message( STATUS "===== FetchContent: s2client_proto" )
FetchContent_Declare(
    s2client_proto
    GIT_REPOSITORY https://github.com/Blizzard/s2client-proto.git
    GIT_TAG 7212ae512d15aa93a708e025d3ab9af4a9c4138f
    GIT_PROGRESS TRUE
    UPDATE_DISCONNECTED TRUE
    SOURCE_SUBDIR "" # Forces CMake to treat this exclusively as a source directory
    PATCH_COMMAND git apply "${CMAKE_CURRENT_LIST_DIR}/s2client_proto_arena_packing.patch"
    )
FetchContent_MakeAvailable( s2client_proto )

#if( CMAKE_DEBUG )
#    set( Protobuf_DEBUG ON )
#endif()

# Glob .proto files
file( GLOB SC2_PROTO
    "${s2client_proto_SOURCE_DIR}/s2clientprotocol/*.proto" )


# Create the output directory for generated protos
set( proto_generation_dir "${PROJECT_BINARY_DIR}/generated" )
file( MAKE_DIRECTORY "${proto_generation_dir}" )

# Compute the expected generated source and header files
set(PROTO_SRCS "")
set(PROTO_HDRS "")
foreach(PROTO_FILE IN LISTS SC2_PROTO)
    get_filename_component(PROTO_NAME "${PROTO_FILE}" NAME_WE)
    list(APPEND PROTO_SRCS "${proto_generation_dir}/${PROTO_NAME}.pb.cc")
    list(APPEND PROTO_HDRS "${proto_generation_dir}/${PROTO_NAME}.pb.h")
endforeach()

# Generate files at build time if .proto files change
add_custom_command(
    OUTPUT ${PROTO_SRCS} ${PROTO_HDRS}
    COMMAND "${Protobuf_PROTOC_EXECUTABLE}"
    --cpp_out=${proto_generation_dir}
    --experimental_allow_proto3_optional
    --cpp_opt=annotate_headers=true
    -I "${s2client_proto_SOURCE_DIR}"
    ${SC2_PROTO}
    DEPENDS ${SC2_PROTO}
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    COMMENT "Running prebuilt protoc.exe on StarCraft II proto files"
    VERBATIM
    )

## Generate files directly using your prebuilt protoc.exe
#execute_process(
#    COMMAND "${Protobuf_PROTOC_EXECUTABLE}"
#    --cpp_out=${proto_generation_dir}
#    --experimental_allow_proto3_optional
#    --cpp_opt=annotate_headers=true
#    -I "${s2client_proto_SOURCE_DIR}"
#    ${SC2_PROTO}
#    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
#    RESULT_VARIABLE protoc_result
#    ERROR_VARIABLE protoc_error
#    )


# sc2protocol will now trigger generation automatically if a .proto file changes
add_library( sc2protocol STATIC ${PROTO_SRCS} ${PROTO_HDRS} )

# Include the generation directory so consumers can find the headers
target_include_directories( sc2protocol PUBLIC "${proto_generation_dir}" )

target_link_libraries( sc2protocol PUBLIC protobuf::libprotobuf )


#include( FindProtobuf )
# Generate C++ headers/sources using the globbed SC2_PROTO files.
#protobuf_generate(
#    TARGET sc2protocol
#    LANGUAGE cpp
#    OUT_VAR PROTO_FILES
#    PROTOC_OUT_DIR "${proto_generation_dir}"
#    PROTOS ${SC2_PROTO}
#    IMPORT_DIRS "${s2client_proto_SOURCE_DIR}"
#    PROTOC_OPTIONS
#    --experimental_allow_proto3_optional
#    --cpp_opt=annotate_headers=true
#    PROTOC_EXE "${PROTOBUF_INSTALL_DIR}/protoc.exe"
#    )

## Target Linking & Header Directories
#target_include_directories( sc2protocol SYSTEM PUBLIC
#    "${proto_generation_dir}"
#    )

# Compiler-Specific Flags and Workarounds
#if( GNU OR CLANG )
#    # GCC / MinGW C++20 Module Workaround:
#    ## GCC's module engine enforces strict linkage checks on header entity exports.
#    ## MSVC handles these natively inside the Global Module Fragment and does not require patching.
#    file( WRITE "${CMAKE_CURRENT_BINARY_DIR}/patch_headers.cmake" [=[
#    file(GLOB_RECURSE PROTO_HEADERS "${HEADERS_DIR}/*.pb.h")
#    foreach(HEADER ${PROTO_HEADERS})
#        file(READ "${HEADER}" CONTENT)
#
#        # Upgrade all 'constexpr' declarations to 'inline constexpr'
#        # This grants external linkage required for C++20 modules while leaving
#        # struct members like TableStruct::offsets (static const) untouched.
#        string(REPLACE "constexpr " "inline constexpr " CONTENT "${CONTENT}")
#
#        # Remove `inline` doubles.
#        string(REPLACE "inline inline" "inline" CONTENT "${CONTENT}")
#        string(REPLACE "inline explicit inline constexpr" "explicit constexpr" CONTENT "${CONTENT}")
#
#        file(WRITE "${HEADER}" "${CONTENT}")
#    endforeach()
#  ]=] )
#elseif( MSVC )
#    target_compile_options( sc2protocol PRIVATE /W0 )
#endif()
message( STATUS "========== END sc2protocol.cmake ==========" )