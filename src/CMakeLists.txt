include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 1. Actually process the subdirectories so their CMakeLists.txt files execute
add_subdirectory(sc2api)
add_subdirectory(sc2lib)
add_subdirectory(sc2protocol)
add_subdirectory(sc2renderer)
add_subdirectory(sc2utils)
# Note: If sc2lib, sc2utils, or renderer have their own CMakeLists.txt files,
# you should add_subdirectory() for them here as well.
# If they don't, you'll need to define them as libraries or add them to bot_sources.
set(bot_sources
    main.cpp
    SchlapBot.cpp
)

add_executable(SchlapBot ${bot_sources})

target_link_libraries(SchlapBot PRIVATE sc2api)

if (BUILD_FOR_LADDER)
    target_compile_definitions(SchlapBot PRIVATE BUILD_FOR_LADDER)
endif ()

if (MSVC)
    target_compile_options(SchlapBot PRIVATE /W4 /EHsc)
else ()
    target_compile_options(SchlapBot PRIVATE -Wall -Wextra -pedantic)
endif ()

if (MINGW)
    target_link_libraries(SchlapBot PRIVATE ssp)
elseif (APPLE)
    target_link_libraries(SchlapBot PRIVATE "-framework Carbon")
# Building on Linux
elseif (UNIX AND NOT APPLE)
    target_link_libraries(SchlapBot PRIVATE pthread dl)
endif ()
