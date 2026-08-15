set(sc2lib_sources
        sc2_action.h
        sc2_errors.h
        sc2_game_settings.cc
        sc2_game_settings.h
        sc2_gametypes.h
        sc2_lib.h
        sc2_typeenums.h
        typeids/sc2_types.h
        "typeids/sc2_${SC2_VERSION}_typeenums.cpp"
        "typeids/sc2_${SC2_VERSION}_typeenums.h"
)

add_library(sc2lib STATIC ${sc2lib_sources})

target_sources(sc2lib
    PUBLIC
        FILE_SET CXX_MODULES
        FILES
        map_data.cppm
        map_info.cppm
)

target_link_libraries(sc2lib PUBLIC sc2utils)
