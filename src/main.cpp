#include <cstddef>
#include <iostream>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "sc2_coordinator.h"
#include "sc2_gametypes.h"
#include "sc2_arg_parser.h"

#include "SchlapBot.h"

using enum sc2::Difficulty;
using enum sc2::Race;

using sc2::AIBuild,
    sc2::ArgParser,
    sc2::Coordinator,
    sc2::LadderSettings,
    std::cout,
    std::size_t,
    std::span,
    std::string,
    std::string_view,
    std::vector;


// #ifdef BUILD_FOR_LADDER
namespace
{

}  // namespace

int main(const int argc, const char* argv[])
{
    const span args(argv, static_cast<size_t>(argc));
    ArgParser::ParseArguments(args);

    const LadderSettings options;
    Coordinator coordinator;
    SchlapBot bot;

    constexpr size_t num_agents = 2;
    coordinator.SetParticipants({ CreateParticipant(Random, &bot, "SchlapBot") });

    cout << "Connecting to port " << options.game_port << '\n';
    coordinator.Connect(options.game_port);
    coordinator.SetupPorts(num_agents, options.start_port, false);

    // NB (alkurbatov): Increase speed of steps processing.
    // Disables ability to control your bot during game.
    // Recommended for competitions.
    coordinator.SetRawAffectsSelection(true);

    coordinator.JoinGame();
    coordinator.SetTimeoutMS(10000);
    std::cout << "Successfully joined game" << '\n';

    while (coordinator.Update())
    {}

    return 0;
}

#else
//
// int main(const int argc, char* argv[])
// {
//     const vector<string_view>  args(argv, argv + argc);
//
//     if (argc < 2)
//     {
//         std::cerr << "IncorporealAIE_v4.SC2Map" << '\n';
//         return 1;
//     }
//
//     Coordinator coordinator;
//     coordinator.LoadSettings(argc, argv);
//     vector<string_view> args(argv, argv + argc);
//     // NOTE: Uncomment to start the game in full screen mode.
//     // coordinator.SetFullScreen(true);
//
//     coordinator.SetRealtime(true);
//
//     SchlapBot bot;
//     coordinator.SetParticipants(
//         {
//             CreateParticipant(Terran, &bot, "SchlapBot"),
//             CreateComputer(
//                 Random,
//                 sc2::Difficulty::CheatInsane,
//                 AIBuild::Rush,
//                 "CheatInsane"
//                 ),
//         });
//
//     coordinator.LaunchStarcraft();
//     coordinator.StartGame(argv[1]);
//
//     while (coordinator.Update())
//     {}
//
//     return 0;
// }
//
// // #endif
