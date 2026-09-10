#include <cstddef>
#include <iostream>
#include <span>
import SchlapBot;
import Coordinator;
import Agent;
import error_handler;
import map_data;
import game_types;

namespace {
using namespace sc2;
using namespace std;
using enum AIBuild;
using enum Difficulty;
using enum Race;
} // namespace

#ifdef BUILD_FOR_LADDER
namespace {
} // namespace

int main ( const int argc, char *const argv[] ) {
    span args ( argv, static_cast<size_t> ( argc ) );
    ArgParser::ParseArguments ( args );

    const LadderSettings options;
    Coordinator          coordinator;
    SchlapBot            bot;

    constexpr size_t num_agents = 2;
    coordinator.SetParticipants (
        { CreateParticipant ( Terran, &bot, "SchlapBot" ) }
    );

    cout << "Connecting to port " << options.game_port << '\n';
    coordinator.Connect ( options.game_port );
    coordinator.SetupPorts ( num_agents, options.start_port, false );

    // NB (alkurbatov): Increase speed of steps processing.
    // Disables ability to control your bot during game.
    // Recommended for competitions.
    coordinator.SetRawAffectsSelection ( true );

    coordinator.JoinGame( );
    coordinator.SetTimeoutMS ( 10'000 );
    std::cout << "Successfully joined game" << '\n';

    while ( coordinator.Update( ) ) { }

    return 0;
} // main Ladder

#else

int main (
    const int argc,
    char     *argv[]
) // NOLINT(*-avoid-c-arrays, *-use-internal-linkage)
{
    const span args ( argv, static_cast<size_t> ( argc ) );

    if ( args.size( ) < 2 ) {
        cerr << "IncorporealAIE_v4" << '\n';
        // return 1;
    }

    Coordinator coordinator;

    if ( coordinator.LoadSettings ( args ) ) {
        cout << "LoadSettings success." << '\n';
    } else {
        SRC_LocationOut ( "LoadSettings failed." );
        abort( );
    }

    coordinator.SetMultithreaded ( true );
    SRC_LocationOut ( "Multithreaded set." );

    // NOTE: Uncomment to start the game in full screen mode.
    // Coordinator.SetFullScreen(true);

    constexpr bool realtime = true;
    coordinator.SetRealtime ( realtime );
    SRC_LocationOut ( format ( "Realtime set: {}", realtime ).c_str( ) );

    SchlapBot Schlap_Bot { };

    coordinator.SetParticipants (
        unordered_map<Agent *, PlayerSetup> {
            { &Schlap_Bot, CreateParticipant ( "SchlapBot", Terran ) },
            { nullptr, CreateComputer ( Random, Easy, Macro ) }
    }
    );

    // sc2_game_settings.cc
    const MapData map_data ( "IncorporealAIE_v4" );

    coordinator.LaunchStarcraft( );
    coordinator.StartGame ( map_data.map_path_new );

    while ( coordinator.Update( ) ) { }

    return 0;
} // Main (Local)
#endif
