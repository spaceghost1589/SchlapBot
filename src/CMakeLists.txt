#if ( BUILD_SC2_RENDERER ) #Process optional Renderer
#add_subdirectory( renderer )
#endif( )

# Define the bot executable and link everything
add_executable(SchlapBot main.cpp)

# Expose source and binary directories globally
target_include_directories(SchlapBot PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}" # <[This]> folder
    "${CMAKE_BINARY_DIR}"
    )

target_include_directories(SchlapBot SYSTEM PUBLIC
    "${PROJECT_BINARY_DIR}/generated"
    )

#if(SCCACHE)
#  add_custom_command(TARGET SchlapBot PRE_BUILD
#      COMMAND SCCACHE_PROGRAM --zero-stats
#      COMMENT "Resetting sccache statistics..."
#      USES_TERMINAL)
#endif()

if(CMAKE_DEBUG)
  if(GNU)
    target_compile_options(SchlapBot PRIVATE -save-temps=cwd)
  elseif(MSVC)
    target_compile_options(SchlapBot PRIVATE
        /P
        /Fi${CMAKE_CURRENT_BINARY_DIR}/preprocessed/
        )
    #Folder for the files created by / Fi
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/src/preprocessed")
  endif()
endif()


#else( )
# #appears to be broken on MinGW / Windows
#target_compile_options( SchlapBot PRIVATE - freport - bug )
#endif( )

target_precompile_headers(SchlapBot PRIVATE
    <vector>
    <string>
    <memory>
    <unordered_map>
    <iostream>
    <civetweb.h>
    <google/protobuf/message.h>
    $<$<BOOL:${BUILD_SC2_RENDERER}>:<SDL.h$<ANGLE-R>>
    )                              # $<ANGLE-R> is `>`

target_link_libraries(
    SchlapBot PUBLIC
    project_warnings
    sc2protocol
    civetweb-c-library
    $<$<BOOL:${BUILD_SC2_RENDERER}>:sc2renderer>)

# Suppress all compilation warnings from dependencies.
if(NOT MSVC AND NOT DEPENDENCY_WARNINGS)
  # target_compile_options(sc2protocol PRIVATE -w)
  target_compile_options(civetweb-c-library PRIVATE -w)
endif()

file(GLOB_RECURSE LEGACY_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    )
target_sources(SchlapBot PRIVATE ${LEGACY_FILES})


set(CMAKE_CXX_SCAN_FOR_MODULES ON)
file(GLOB_RECURSE MODULES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cppm"
    )
#Remove server.cppm as it's duplicate code. Same function as connection.cppm
list(REMOVE_ITEM MODULES "${CMAKE_CURRENT_SOURCE_DIR}/api/Protocol/server.cppm")

set_source_files_properties ( # Disable PCH force-inclusion for module files
				${MODULES} # The invisible header interferes with the module header
				PROPERTIES
				    SKIP_PRECOMPILE_HEADERS ON # which needs to be the first line
				)
#set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/lib/map_data.cppm PROPERTIES
#        COMPILE_OPTIONS "-save-temps=obj;-freport-bug"
#)

target_sources(SchlapBot PUBLIC
    FILE_SET CXX_MODULES FILES
    ${MODULES})

#Platform - specific system networking and threading libraries
if(WIN32)
  target_link_libraries(SchlapBot PUBLIC ws2_32 winmm)
endif()

if(BUILD_FOR_LADDER)
  target_compile_definitions(SchlapBot PRIVATE BUILD_FOR_LADDER)
endif()
