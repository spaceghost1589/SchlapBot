set (CXX_SCAN_FOR_MODULES ON)
set (renderer_sources
     renderer.cppm
     )

add_library (renderer STATIC ${renderer_sources})

set_target_properties (renderer PROPERTIES FOLDER utilities)

target_include_directories (renderer SYSTEM PRIVATE "${sdl_SOURCE_DIR}/include")

target_link_libraries (renderer PRIVATE SDL2-static)
#target_link_libraries(sc2renderer PRIVATE SDL3-static)
