#set(sc2lib_sources
#        action.h
#        errors.h
#        game_settings.cc
#        game_settings.h
#        gametypes.h
#        lib.h
#        type_enums.h
#        typeids/types.h
#        "typeids/sc2_${SC2_VERSION}_typeenums.cpp"
#        "typeids/sc2_${SC2_VERSION}_typeenums.h"
#)
#
#add_library(sc2lib STATIC ${sc2lib_sources})
#
##target_sources(sc2lib
##    PUBLIC
##        FILE_SET CXX_MODULES
##        FILES
##        map_data.cppm
##        map_info.cppm
##)
#
#target_link_libraries(sc2lib PUBLIC sc2utils)
