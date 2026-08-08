message(STATUS "FetchContent: cpp-sc2")

FetchContent_Declare(
        cpp-sc2
        GIT_REPOSITORY https://github.com/cpp-sc2/cpp-sc2.git
        GIT_TAG master
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(cpp-sc2)