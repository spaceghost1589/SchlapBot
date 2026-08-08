set(bot_sources
    main.cpp
    SchlapBot.cpp
)

add_executable(SchlapBot ${bot_sources})

target_link_libraries(SchlapBot PRIVATE
    sc2api
    sc2lib
    sc2utils
    sc2protocol
)

if (BUILD_FOR_LADDER)
    target_compile_definitions(SchlapBot PRIVATE BUILD_FOR_LADDER)
endif ()

if (MSVC)
    target_compile_options(SchlapBot PRIVATE /W4 /EHsc)
else ()
    target_compile_options(SchlapBot PRIVATE -Wall -Wextra -pedantic)
endif ()

target_link_libraries(SchlapBot PRIVATE cpp_sc2)

if (MINGW)
    target_link_libraries(SchlapBot PRIVATE ssp)
elseif (APPLE)
    target_link_libraries(SchlapBot PRIVATE "-framework Carbon")
# Building on Linux
elseif (UNIX AND NOT APPLE)
    target_link_libraries(SchlapBot PRIVATE pthread dl)
endif ()
