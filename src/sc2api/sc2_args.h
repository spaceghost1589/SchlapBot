#pragma once

#include <span>

#include "sc2_game_settings.h"

namespace sc2 {

using std::span;

bool ParseFromFile(ProcessSettings& process_settings, GameSettings& game_settings, const std::string& file_name);
bool ParseSettings(span<const char*> args, ProcessSettings& process_settings, GameSettings& game_settings);

}  // namespace sc2
