# Inject sources specific for particular version of the game client
#file(
#  WRITE "${CMAKE_CURRENT_BINARY_DIR}/type_enums.h"
#  "#pragma once
#
##include \"typeids/sc2_${SC2_VERSION}_typeenums.h\"
#")

#set(sc2api_sources
#    agent.cc
#    agent.h
#    api.h
#    args.cc
#    args.h
#    client.cc
#    client.h
#    common.h
#    connection.cc
#    connection.h
#    control_interfaces.h
#    coordinator.cc
#    coordinator.h
#    data.cc
#    data.h
#    interfaces.h
#    proto_interface.cc
#    proto_interface.h
#    proto_to_pods.cc
#    proto_to_pods.h
#    replay_observer.cc
#    replay_observer.h
#    score.cc
#    score.h
#    search.cc
#    search.h
#    server.cc
#    server.h
#    unit.cc
#    unit.h
#    unit_filters.cc
#    unit_filters.h)

#add_library(sc2api STATIC ${sc2api_sources})

#target_include_directories(
#  sc2api PUBLIC "${PROJECT_SOURCE_DIR}/src"
#                "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>")

#target_include_directories(sc2api SYSTEM
#                           PUBLIC "${civetweb_SOURCE_DIR}/include")
#
#target_link_libraries(sc2api PUBLIC sc2lib sc2protocol sc2utils
#                                    civetweb-c-library)
#
## Platform-specific system networking and threading libraries
#if(WIN32)
#  target_link_libraries(sc2api PUBLIC ws2_32 winmm)
#endif()
