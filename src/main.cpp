#include <cstddef>
#include <iostream>
#include <span>

#include "sc2api/sc2_coordinator.h"
#include "sc2lib/sc2_gametypes.h"

import SchlapBot;
import map_data;

using sc2::SchlapBot,
    sc2::AIBuild,
    sc2::Coordinator,
    sc2::Difficulty,
    sc2::MapData,
    sc2::Race,
    std::cout,
    std::cerr,
    std::size_t,
    std::span;

using enum AIBuild;
using enum Difficulty;
using enum Race;


#ifdef BUILD_FOR_LADDER
namespace
{

}  // namespace

int main(const int argc, char* const argv[])
{
    span args(argv, static_cast<size_t>(argc));
    ArgParser::ParseArguments(args);

    const LadderSettings options;
    Coordinator coordinator;
    SchlapBot bot;

    constexpr size_t num_agents = 2;
    coordinator.SetParticipants({ CreateParticipant(Terran, &bot, "SchlapBot") });

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
} // main Ladder

#else

int main(int argc, char* argv[]) // NOLINT(*-avoid-c-arrays, *-use-internal-linkage)
{
    span args(argv, static_cast<size_t>(argc));

    if (args.size() < 2)
    {
        cerr << "IncorporealAIE_v4" << '\n';
        // return 1;
    }

    Coordinator coordinator;
    if (coordinator.LoadSettings(args)) {
        cout << "LoadSettings success." << '\n';
    } else {
        cerr << "LoadSettings failed." << '\n';
        abort();
    }

    // NOTE: Uncomment to start the game in full screen mode.
    // coordinator.SetFullScreen(true);

    coordinator.SetRealtime(true);

    SchlapBot bot{};

    coordinator.SetParticipants( {
            CreateParticipant (
                Terran,
                &bot,
                "SchlapBot"
            ),
            CreateComputer(
                Random,
                Easy,
                Macro
            ),
        } );

    // sc2_game_settings.cc
    const MapData map_data("IncorporealAIE_v4");

    coordinator.LaunchStarcraft();
    coordinator.StartGame(map_data.map_path_new);

    while (coordinator.Update())
    {}

    return 0;
} // Main (Local)
#endif
