message( STATUS "===== FetchContent: protocol" )

FetchContent_Declare(
    s2client_proto
    GIT_REPOSITORY https://github.com/Blizzard/s2client-proto.git
    GIT_TAG 7212ae512d15aa93a708e025d3ab9af4a9c4138f
    GIT_PROGRESS TRUE
    UPDATE_DISCONNECTED TRUE
    PATCH_COMMAND git apply "${CMAKE_CURRENT_LIST_DIR}/s2client_proto_arena_packing.patch"
    )
FetchContent_MakeAvailable( s2client_proto )

if( CMAKE_DEBUG )
    set( Protobuf_DEBUG ON )
endif()

# Glob .proto files.
file( GLOB SC2_PROTO
    "${s2client_proto_SOURCE_DIR}/s2clientprotocol/*.proto" )
add_library( sc2protocol STATIC ${SC2_PROTO} )

# Create the output directory for generated protos.
set(proto_generation_dir "${PROJECT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY "${proto_generation_dir}")

include(FindProtobuf)
# Generate C++ headers/sources using the globbed SC2_PROTO files.
protobuf_generate(
    TARGET sc2protocol
    LANGUAGE cpp
    OUT_VAR PROTO_FILES
    PROTOC_OUT_DIR "${proto_generation_dir}"
    PROTOS ${SC2_PROTO}
    IMPORT_DIRS "${s2client_proto_SOURCE_DIR}"
    PROTOC_OPTIONS
    --experimental_allow_proto3_optional
    --cpp_opt=annotate_headers=true
#    PROTOC_EXE ${PROJECT_SOURCE_DIR}/include/protoc/protoc.exe
    )

# Target Linking & Header Directories
target_include_directories( sc2protocol SYSTEM PUBLIC
    "${proto_generation_dir}"
    )

target_link_libraries( sc2protocol PUBLIC protobuf::libprotobuf )

# Compiler-Specific Flags and Workarounds
if(GNU OR CLANG)
  # GCC / MinGW C++20 Module Workaround:
  ## GCC's module engine enforces strict linkage checks on header entity exports.
  ## MSVC handles these natively inside the Global Module Fragment and does not require patching.
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

add_custom_command (
    TARGET sc2protocol POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -DHEADERS_DIR=${CMAKE_CURRENT_BINARY_DIR}/s2clientprotocol
    -P ${CMAKE_CURRENT_BINARY_DIR}/patch_headers.cmake
    COMMENT "Patching generated Protobuf headers for C++20 module compatibility..."
    )

  # Create a custom command that outputs a stamp file and DEPENDS on the generated protos.
  add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/patch_proto_headers.stamp"
    COMMAND ${CMAKE_COMMAND}
    -DHEADERS_DIR=${PROJECT_BINARY_DIR}/s2clientprotocol
    -P ${CMAKE_CURRENT_BINARY_DIR}/patch_headers.cmake
    COMMAND ${CMAKE_COMMAND} -E touch "${CMAKE_CURRENT_BINARY_DIR}/patch_proto_headers.stamp"
    DEPENDS ${PROTO_FILES}
    COMMENT "Patching generated Protobuf headers for C++20 module compatibility..."
    )
  # Attach the stamp file directly to the target sources to enforce build order.
  target_sources(sc2protocol PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/patch_proto_headers.stamp")

elseif(MSVC)
  target_compile_options(sc2protocol PRIVATE /W0)
endif()
