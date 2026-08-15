# Broadly expose the 'src' folder and the binary output folder to ALL
# subdirectories added below. This solves both sc2utils and sc2api missing header errors.
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_BINARY_DIR}
)

# 1. Actually process the subdirectories so their CMakeLists.txt files execute
add_subdirectory(sc2utils)
add_subdirectory(sc2lib)
add_subdirectory(sc2api)
if (BUILD_SC2_RENDERER)
    add_subdirectory(sc2renderer)
endif ()


add_executable(SchlapBot main.cpp)

set (CMAKE_CXX_MODULE_STD 1) # Tells CMake to build `import std`
set (CMAKE_CXX_SCAN_FOR_MODULES ON)

if (MINGW)
    target_link_options(SchlapBot PRIVATE -mconsole)
endif ()

target_sources(SchlapBot
    PUBLIC
        FILE_SET CXX_MODULES
        FILES
        SchlapBot.cppm
)

target_link_libraries(SchlapBot PUBLIC
        project_warnings
        sc2protocol
        sc2utils
        sc2lib
        sc2api
        $<$<BOOL:${BUILD_SC2_RENDERER}>:sc2renderer>
)

if (BUILD_FOR_LADDER)
    target_compile_definitions(SchlapBot PRIVATE BUILD_FOR_LADDER)
endif ()
