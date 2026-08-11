/*! \file sc2_gametypes.h
    \brief Types used in setting up a game.
*/
#pragma once

#include <array>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "sc2_common.h"



namespace sc2 {

using std::array,
	std::ostringstream,
	std::ranges::all_of,
	std::string,
	std::string_view,
	std::uint8_t,
	std::vector;
using Tag = uint64_t;


static constexpr Tag NullTag = 0LL;

enum class Race : uint8_t {
	Terran = 1,
	Zerg = 2,
	Protoss = 3,
	Random = 4,
};
using enum Race;

inline string_view RaceToString(const Race race)
{
	switch (race) {
	case Terran:  return "Terran";
	case Zerg:    return "Zerg";
	case Protoss: return "Protoss";
	case Random:  return "Random";
	}
	return "Is idiot a Race?";
}

enum class Difficulty : uint8_t {
    VeryEasy = 1,
    Easy = 2,
    Medium = 3,
    MediumHard = 4,
    Hard = 5,
    HardVeryHard = 6,
    VeryHard = 7,
    CheatVision = 8,
    CheatMoney = 9,
    CheatInsane = 10,
};
using enum Difficulty;

inline string_view DifficultyToString(const Difficulty difficulty)
{
	switch (difficulty) {
	case VeryEasy:     return "Very Easy";
	case Easy:         return "Easy";
	case Medium:       return "Medium";
	case MediumHard:   return "Medium Hard";
	case Hard:         return "Hard";
	case HardVeryHard: return "Hard Very Hard";
	case VeryHard:     return "Very Hard";
	case CheatVision:  return "Cheat Vision";
	case CheatMoney:   return "Cheat Money";
	case CheatInsane:  return "Cheat Insane";
	}
	return "Is keyboard slamming a difficulty?";
}

enum class AIBuild : uint8_t {
	RandomBuild = 1,
	Rush = 2,
	Timing = 3,
	Power = 4,
	Macro = 5,
	Air = 6,
};
using enum AIBuild;

inline string_view AIBuildToString(const AIBuild build)
{
	switch (build) {
	case RandomBuild: return "Random Build";
	case Rush:        return "Rush";
	case Timing:      return "Timing";
	case Power:       return "Power";
	case Macro:       return "Macro";
	case Air:         return "Air";
	}
	return "no AIBuild";
} // AIBuildToString

enum class PlayerType : uint8_t {
	Participant = 1,
	Computer = 2,
	Observer = 3,
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

class Agent;

//! Setup for a player in a game.
struct PlayerSetup {
    //! Player can be a Participant (usually an agent), Computer (in-built AI) or Observer.
    PlayerType type = Participant;
    //! Agent, if one is available.
    Agent* agent = nullptr;
    //! Name of this player.
    string player_name;

    // Only used for Computer

    //! Race: Terran, Zerg, Protoss, or Random. Only for playing against the built-in AI.
	Race race = Random;
    //! Difficulty: Only for playing against the built-in AI.
	Difficulty difficulty = Easy;
    //! Build type, used by computer opponent.
	AIBuild ai_build = RandomBuild;

    PlayerSetup();

    PlayerSetup(const PlayerType in_type,
    			const Race in_race,
    			Agent* in_agent = nullptr,
    			string in_player_name = "",
                const Difficulty in_difficulty = Easy,
                const AIBuild in_ai_build = RandomBuild)
        : type(in_type),
          agent(in_agent),
          player_name(std::move(in_player_name)),
          race(in_race),
          difficulty(in_difficulty),
          ai_build(in_ai_build) {}
};

static PlayerSetup CreateParticipant(const Race race,
										   Agent* agent,
									 const string& player_name) {
    return {Participant,
    		race,
    		agent,
    		player_name};
}

static PlayerSetup CreateComputer(const Race race = Random,
								  const Difficulty difficulty = Easy,
								  const AIBuild ai_build = RandomBuild,
                                  const string& player_name = "") {

	// Generates computer's name based on settings if no name is passed.
	if (string final_name = player_name; final_name.empty()) {
		ostringstream name_stream;
		name_stream << "Computer-"
					<< RaceToString(race) << "-"
					<< DifficultyToString(difficulty) << "-"
					<< AIBuildToString(ai_build);
		final_name = name_stream.str();
	}
	return {Computer,
    		race,
    		nullptr,
    		player_name,
    		difficulty,
    		ai_build};
}

//! Port setup for a client.
struct PortSet {
    int game_port{-1};
    int base_port{-1};

    PortSet() = default;

    [[nodiscard]] bool IsValid() const {
        return game_port > 0 && base_port > 0;
    }
};

//! Port setup for one or more clients in a game.
struct Ports {
    PortSet server_ports;
    vector<PortSet> client_ports;
    int shared_port{-1};

    Ports();

    [[nodiscard]] bool IsValid() const {
        if (shared_port < 1) {
            return false;
		}
        if (!server_ports.IsValid()) {
            return false;
		}
        if (client_ports.empty()) {
            return false;
		}
        return all_of(client_ports, [&](const auto& PortSet) {
	        return PortSet.IsValid();
        });
    }
};

static constexpr int max_path_size = 512;
static constexpr int max_version_size = 32;
static constexpr int max_num_players = 16;

//! Information about a player in a replay.
struct ReplayPlayerInfo {
    //! Player ID.
    int player_id{0};
    //! Player ranking.
    int mmr{-10000};
    //! Player actions per minute.
    int apm{0};
    //! Actual player race.
    Race race{Random};
    //! Selected player race. If the race is "Random", the race data member may be different.
    Race race_selected{Random};
    //! If the player won or lost.
    GameResult game_result{Undecided};

    ReplayPlayerInfo() = default;
};

//! Information about a replay file.
struct ReplayInfo {
    float duration{0.0F};
    unsigned int duration_gameloops{0};
    int32_t num_players{0};
    uint32_t data_build{0};
    uint32_t base_build{0};
    string map_name;
    string map_path;
    string replay_path;
    string version;
    string data_version;
	array<ReplayPlayerInfo, max_num_players> players;

    ReplayInfo();

    bool GetPlayerInfo(ReplayPlayerInfo& replay_player_info, const int playerID) const {
        for (int i = 0; i < num_players; ++i) {
            if (playerID == players.at(i).player_id) {
                replay_player_info = players.at(i);
                return true;
            }
        }

        return false;
    }

    [[nodiscard]] float GetGameloopsPerSecond() const {
        return static_cast<float>(duration_gameloops) / duration;
    }
};  // struct ReplayInfo

struct PlayerResult {
    PlayerResult(const uint32_t player_id,
    			 const GameResult result)
		: player_id(player_id),
		result(result) {}

    uint32_t player_id{0};
    GameResult result = Undecided;
};

struct ChatMessage {
    uint32_t player_id{0};
    string message;
};

}  // namespace sc2
