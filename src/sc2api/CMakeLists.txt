# Inject sources specific for particular version of the game client
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/sc2_typeenums.h"
"#pragma once

#include \"typeids/sc2_${SC2_VERSION}_typeenums.h\"
"
)

set(sc2api_sources
    sc2_agent.cc
    sc2_agent.h
    sc2_api.h
    sc2_args.cc
    sc2_args.h
    sc2_client.cc
    sc2_client.h
    sc2_common.cc
    sc2_common.h
    sc2_connection.cc
    sc2_connection.h
    sc2_control_interfaces.h
    sc2_coordinator.cc
    sc2_coordinator.h
    sc2_data.cc
    sc2_data.h
    sc2_interfaces.h
    sc2_proto_interface.cc
    sc2_proto_interface.h
    sc2_proto_to_pods.cc
    sc2_proto_to_pods.h
    sc2_replay_observer.cc
    sc2_replay_observer.h
    sc2_score.cc
    sc2_score.h
    sc2_search.cc
    sc2_search.h
    sc2_server.cc
    sc2_server.h
    sc2_unit.cc
    sc2_unit.h
    sc2_unit_filters.cc
    sc2_unit_filters.h
)

add_library(sc2api STATIC ${sc2api_sources})

target_include_directories(sc2api PUBLIC
    "${PROJECT_SOURCE_DIR}/src"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
)

target_include_directories(sc2api SYSTEM PUBLIC "${civetweb_SOURCE_DIR}/include")

target_link_libraries(sc2api PUBLIC sc2lib sc2protocol sc2utils civetweb-c-library)

# Platform-specific system networking and threading libraries
if(WIN32)
    target_link_libraries(sc2api PUBLIC ws2_32 winmm)
endif()
