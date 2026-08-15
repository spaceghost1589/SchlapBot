#pragma once

#include <span>

#include "sc2lib/sc2_game_settings.h"
#include "sc2utils/sc2_arg_parser.h"

namespace sc2 {

using std::span,
    std::string;

bool ParseFromFile(ProcessSettings& process_settings, GameSettings& game_settings, const std::string& file_name);
bool ParseSettings(span<char*> args, ProcessSettings& process_settings, GameSettings& game_settings);

// TODO refactor this and AddOptions() to `constexpr` for faster init time. array + string_view
inline const vector<Arg>& options_ {
    {.abbreviation_="-e",
        .fullname_="--executable",
        .description_="The path to StarCraft II.",
        .required_=false},
     {.abbreviation_="-s",
         .fullname_="--step_size",
         .description_="How many steps to take per call.",
         .required_=false},
     {.abbreviation_="-p",
         .fullname_="--port",
         .description_="The port to make StarCraft II listen on.",
         .required_=false},
     {.abbreviation_="-r",
         .fullname_="--realtime",
         .description_="Whether to run StarCraft II in real time or not.",
         .required_=false},
     {.abbreviation_="-m",
         .fullname_="--map",
         .description_="Which map to run.",
         .required_=false},
     {.abbreviation_="-t",
         .fullname_="--timeout",
         .description_="Timeout for how long the library will block for a response.",
         .required_=false},
     {.abbreviation_="-d",
         .fullname_="--data_version",
         .description_="Data hash of the game version to run (see versions.json)",
         .required_=false}
};

}  // namespace sc2
