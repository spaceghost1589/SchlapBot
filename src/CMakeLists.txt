# Expose source and binary directories globally
include_directories (${CMAKE_CURRENT_SOURCE_DIR} # <[This]> folder
                     #                     ${CMAKE_CURRENT_BINARY_DIR} #
                     ${CMAKE_BINARY_DIR} # <root>/out/build/<Preset_Name>
                     )

add_subdirectory (api)
add_subdirectory (utils)
add_subdirectory (lib)
if (BUILD_SC2_RENDERER) # Process optional Renderer
	add_subdirectory (renderer)
endif ()

# Define the bot executable and link everything
add_executable (SchlapBot main.cpp
api/interface/action_interface.cppm)

if (CACHE_DEPENDENCIES)
	target_precompile_headers (SchlapBot PRIVATE
	                           <vector>
	                           <string>
	                           <memory>
	                           <unordered_map>
	                           <iostream>
	                           <civetweb.h>
	                           <google/protobuf/message.h>
	                           $<$<BOOL:${BUILD_SC2_RENDERER}>:<SDL.h$<ANGLE-R>>
	                           )                              # $<ANGLE-R> is `>`
endif ()

target_link_libraries (
				SchlapBot PUBLIC
				project_warnings
				sc2protocol
				civetweb-c-library
				$<$<BOOL:${BUILD_SC2_RENDERER}>:sc2renderer>)

file (GLOB_RECURSE LEGACY_FILES CONFIGURE_DEPENDS
      "api/*.cc" "api/*.h"
      "lib/*.cc" "lib/*.cpp" "lib/*.h"
      "utils/*.cc" "utils/*.h")
target_sources (SchlapBot PRIVATE ${LEGACY_FILES})

set (CMAKE_CXX_SCAN_FOR_MODULES ON)
file (GLOB_RECURSE MODULES CONFIGURE_DEPENDS
      "api/*.cppm"
      "lib/*.cppm"
      "renderer/*.cppm"
      "utils/*.cppm"
      )
set_source_files_properties ( # Disable PCH force-inclusion for module files
				${MODULES} # The invisible header interferes with the module header
				PROPERTIES SKIP_PRECOMPILE_HEADERS ON # which needs to be the first line
				)
target_sources (SchlapBot PUBLIC
                FILE_SET CXX_MODULES
                FILES
                ${MODULES}
                SchlapBot.cppm
                )

# Platform-specific system networking and threading libraries
if (WIN32)
	target_link_libraries (SchlapBot PUBLIC ws2_32 winmm)
endif ()

if (BUILD_FOR_LADDER)
	target_compile_definitions (SchlapBot PRIVATE BUILD_FOR_LADDER)
endif ()
