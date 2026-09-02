module;
// #include <algorithm>
// #include <array>
// #include <functional>
// #include <sstream>
// #include <string>
// #include <string_view>
// #include <utility>
// #include <vector>

#include "utils/arg_parser.h"
export module game_types;
import std;

namespace {
class Agent;
} // namespace

export namespace sc2 {
using namespace std;

using Tag = uint64_t;

inline constexpr Tag NullTag = 0ll;

enum class Race : uint8_t {
    NoRace  = 0,
    Terran  = 1,
    Zerg    = 2,
    Protoss = 3,
    Random  = 4,
};
using enum Race;

inline string_view RaceToString ( const Race race ) {
    switch ( race ) {
        case NoRace  : return "No Race";
        case Terran  : return "Terran";
        case Zerg    : return "Zerg";
        case Protoss : return "Protoss";
        case Random  : return "Random";
    }
    return "Is idiot a Race?";
}


enum class Difficulty : uint8_t { // 4 bits
    VeryEasy     = 1,
    Easy         = 2,
    Medium       = 3,
    MediumHard   = 4,
    Hard         = 5,
    HardVeryHard = 6,
    VeryHard     = 7,
    CheatVision  = 8,
    CheatMoney   = 9,
    CheatInsane  = 10,
};
using enum Difficulty;

inline string_view DifficultyToString ( const Difficulty difficulty ) {
    switch ( difficulty ) {
        case VeryEasy     : return "Very Easy";
        case Easy         : return "Easy";
        case Medium       : return "Medium";
        case MediumHard   : return "Medium Hard";
        case Hard         : return "Hard";
        case HardVeryHard : return "Hard Very Hard";
        case VeryHard     : return "Very Hard";
        case CheatVision  : return "Cheat Vision";
        case CheatMoney   : return "Cheat Money";
        case CheatInsane  : return "Cheat Insane";
    }
    return "Is keyboard slamming a difficulty?";
}

enum class AIBuild : uint8_t { // 3 bits
    RandomBuild = 1,
    Rush        = 2,
    Timing      = 3,
    Power       = 4,
    Macro       = 5,
    Air         = 6,
};
using enum AIBuild;

inline string_view AIBuildToString ( const AIBuild build ) {
    switch ( build ) {
        case Rush   : return "Rush";
        case Timing : return "Timing";
        case Power  : return "Power";
        case Macro  : return "Macro";
        case Air    : return "Air";
        default     : return "Random Build";
    }
} // AIBuildToString

// struct DifficultyBuildBitMask
// {
//     uint8_t DifficultyAndAIBuild;
//
//     DifficultyBuildBitMask ( Difficulty difficulty, AIBuild AI_build )
//           : DifficultyAndAIBuild (
//                 ( static_cast<uint8_t> ( difficulty ) << 0 ) |
//                 ( static_cast<uint8_t> ( AI_build ) << 4 )
//             ) {}
//
//     Difficulty DifficultyUnmerge ( ) const {
//         return static_cast<Difficulty> ( DifficultyAndAIBuild >> 0 );
//     }
//
//     AIBuild AIBuildUnmerge ( ) const {
//         return static_cast<AIBuild> ( DifficultyAndAIBuild >> 4 );
//     }
// };
//
// // using Difficulty =
// //     function<static_cast<Difficulty> ( DifficultyBuildBitMask
// //                                            .DifficultyUnmerge( ) )>;


enum class PlayerType : uint8_t {
    Participant = 1,
    Computer    = 2,
    Observer    = 3,
};
using enum PlayerType;


enum class GameResult : uint8_t {
    Win,
    Loss,
    Tie,
    Undecided,
};
using enum GameResult;


enum class ChatChannel : uint8_t { All = 0, Team = 1 };


//! Setup for a player in a game.
struct PlayerSetup
{
    //! Name of this player.
    string     player_name;
    /*! Player can be a Participant (usually an agent), Computer (in-built AI)
     * or Observer. */
    PlayerType type;


    // Only used for Computer
    /*! Race: Terran, Zerg, Protoss, or Random. Only for playing against the
     * built-in AI. */
    Race       race { Random };
    //! Difficulty: Only for playing against the built-in AI.
    Difficulty difficulty { Easy };
    //! Build type, used by computer opponent.
    AIBuild    ai_build { RandomBuild };

    PlayerSetup ( );

    PlayerSetup (
        const PlayerType in_type,
        const Race       in_race,
        string           in_player_name = "",
        const Difficulty in_difficulty  = Easy,
        const AIBuild    in_ai_build    = RandomBuild
    )
          : type ( in_type ),
            player_name ( std::move ( in_player_name ) ),
            race ( in_race ),
            difficulty ( in_difficulty ),
            ai_build ( in_ai_build ) {}
};

//! Port setup for a client.
struct PortSet
{
    int game_port { -1 };
    int base_port { -1 };

    PortSet ( ) = default;

    [[nodiscard]]
    bool IsValid ( ) const {
        return game_port > 0 && base_port > 0;
    }
};

//! Port setup for one or more clients in a game.
struct Ports
{
    PortSet         server_ports;
    vector<PortSet> client_ports;
    int             shared_port { -1 };

    Ports ( ) = default;

    [[nodiscard]]
    bool IsValid ( ) const {
        if ( shared_port < 1 ) {
            return false;
        }
        if ( !server_ports.IsValid( ) ) {
            return false;
        }
        if ( client_ports.empty( ) ) {
            return false;
        }
        return ranges::all_of ( client_ports, [&] ( const auto& PortSet ) {
            return PortSet.IsValid( );
        } );
    }
};

constexpr int max_path_size    = 512;
constexpr int max_version_size = 32;
constexpr int max_num_players  = 16;

//! Information about a player in a replay.
struct ReplayPlayerInfo
{
    //! Player ID.
    int        player_id { 0 };
    //! Player ranking.
    int        mmr { -10000 };
    //! Player actions per minute.
    int        apm { 0 };
    //! Actual player race.
    Race       race { Random };
    //! Selected player race. If the race is "Random", the race data member may
    //! be different.
    Race       race_selected { Random };
    //! If the player won or lost.
    GameResult game_result { Undecided };

    ReplayPlayerInfo ( ) = default;
};

//! Information about a replay file.
struct ReplayInfo
{
    float                                    duration { 0.0F };
    unsigned int                             duration_gameloops { 0 };
    int32_t                                  num_players { 0 };
    uint32_t                                 data_build { 0 };
    uint32_t                                 base_build { 0 };
    string                                   map_name;
    string                                   map_path;
    string                                   replay_path;
    string                                   version;
    string                                   data_version;
    array<ReplayPlayerInfo, max_num_players> players;

    ReplayInfo ( ) = default;

    bool GetPlayerInfo (
        ReplayPlayerInfo& replay_player_info, const int playerID
    ) const {
        for ( int i = 0; i < num_players; ++i ) {
            if ( playerID == players.at ( i ).player_id ) {
                replay_player_info = players.at ( i );
                return true;
            }
        }

        return false;
    }

    [[nodiscard]]
    float GetGameloopsPerSecond ( ) const {
        return static_cast<float> ( duration_gameloops ) / duration;
    }
}; // struct ReplayInfo

struct PlayerResult
{
    PlayerResult ( const uint32_t player_id, const GameResult result )
          : player_id ( player_id ),
            result ( result ) {}

    uint32_t   player_id { 0 };
    GameResult result = Undecided;
};

struct ChatMessage
{
    uint32_t player_id { 0 };
    string   message;
};

} // namespace sc2
