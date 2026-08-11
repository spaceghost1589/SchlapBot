#include "sc2_args.h"

#include <cassert>
#include <cstdlib>
#include <iostream>

#include "sc2utils/sc2_arg_parser.h"
#include "sc2utils/sc2_manage_process.h"
#include "sc2utils/sc2_property_reader.h"

namespace sc2 {

using std::span;

static auto StarCraft2UserDirectory = "StarCraft II";
static auto StarCraft2ExecuteInfo = "ExecuteInfo.txt";

bool ParseFromFile(ProcessSettings& process_settings, GameSettings& game_settings, const std::string& file_name) {
    PropertyReader reader;

    if (!reader.LoadFile(file_name)) {
        return false;
    }

    reader.ReadString("executable", process_settings.process_path);

    int real_time = 0;
    reader.ReadInt("realtime", real_time);
    process_settings.realtime = real_time;

    reader.ReadInt("port", process_settings.port_start);
    reader.ReadString("map", game_settings.map_name);
    reader.ReadInt("timeout", process_settings.timeout_ms);
    return true;
}

#if defined(_WIN32)
const char kDirectoryDivider = '\\';
#else
const char kDirectoryDivider = '/';
#endif

std::string ParseExecuteInfo(ProcessSettings& process_settings, GameSettings& game_settings) {
    std::string execute_info_filepath = GetUserDirectory();
    if (execute_info_filepath.empty()) {
        return "Failed to determine path to the user's directory";
    }

    execute_info_filepath += kDirectoryDivider;
    execute_info_filepath += StarCraft2UserDirectory;
    execute_info_filepath += kDirectoryDivider;
    execute_info_filepath += StarCraft2ExecuteInfo;

    if (!ParseFromFile(process_settings, game_settings, execute_info_filepath)) {
        return "Failed to parse " + execute_info_filepath;
    }

    if (!FindLatestExe(process_settings.process_path)) {
        return "Failed to find latest StarCraft II executable in " + process_settings.process_path;
    }

    return {};
}

bool ParseSettings(const span<const char*> args, ProcessSettings& process_settings, GameSettings& game_settings) {
    ArgParser arg_parser(args.front());

    // NB (alkurbatov): First attempt to parse from the SC2 user directory.
    // Note that ExecuteInfo.txt may be missing on Linux and command line
    // options should be used instead.
    std::string parse_error = ParseExecuteInfo(process_settings, game_settings);

    arg_parser.AddOptions(
        {{.abbreviation_="-e", .fullname_="--executable", .description_="The path to StarCraft II.", .required_=false},
         {.abbreviation_="-s", .fullname_="--step_size", .description_="How many steps to take per call.", .required_=false},
         {.abbreviation_="-p", .fullname_="--port", .description_="The port to make StarCraft II listen on.", .required_=false},
         {.abbreviation_="-r", .fullname_="--realtime", .description_="Whether to run StarCraft II in real time or not.", .required_=false},
         {.abbreviation_="-m", .fullname_="--map", .description_="Which map to run.", .required_=false},
         {.abbreviation_="-t", .fullname_="--timeout", .description_="Timeout for how long the library will block for a response.", .required_=false},
         {.abbreviation_="-d", .fullname_="--data_version", .description_="Data hash of the game version to run (see versions.json)", .required_=false}});

    if (const char* sc2path = std::getenv("SC2PATH")) {
        process_settings.process_path = sc2path;
    }

    if (!arg_parser.Parse(const span<const char*> args)) {
        return false;
    }

    arg_parser.Get("executable", process_settings.process_path);
    if (process_settings.process_path.length() < 2) {
        std::cerr << "Path to StarCraft II executable is not specified.\n";

        if (!parse_error.empty()) {
            std::cerr << parse_error << '\n';
        }

        std::cerr << "Please run StarCraft II before running this application or provide command line arguments.\n";
        std::cerr << "For more options: " << argv[0] << " --help\n\n";

        return false;
    }

    std::string step_size;
    if (arg_parser.Get("step_size", step_size)) {
        process_settings.step_size = atoi(step_size.c_str());
    }

    std::string realtime;
    if (arg_parser.Get("realtime", realtime)) {
        process_settings.realtime = realtime == "true";
    }

    std::string timeout;
    if (arg_parser.Get("timeout", timeout)) {
        process_settings.timeout_ms = atoi(timeout.c_str());
    }

    std::string data_version;
    if (arg_parser.Get("data_version", data_version)) {
        process_settings.data_version = data_version;
    }

    arg_parser.Get("map", game_settings.map_name);

    return true;
}

}  // namespace sc2
