message(STATUS "FetchContent: protocol")

FetchContent_Declare(
    sc2protocol
    GIT_REPOSITORY https://github.com/Blizzard/s2client-proto.git
    GIT_TAG 7212ae512d15aa93a708e025d3ab9af4a9c4138f
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(sc2protocol)
