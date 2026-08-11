#pragma once

#include <cstdint>
#include <span>
#include <string>
#include <unordered_map>
#include <vector>

namespace sc2 {

using std::int32_t,
    std::span,
    std::string,
    std::string_view,
    std::unordered_map,
    std::vector;

struct LadderSettings{
	int32_t game_port{0};
	int32_t start_port{0};
	string ladder_server;
	string opponent_id;
};

struct Arg {
    string abbreviation_;
    string fullname_;
    string description_;
    bool required_{false};
};

class ArgParser {
public:
    // constructors
    ArgParser() = default;
    explicit ArgParser(string_view executable_name);
    ArgParser(string usage, string description, string example);

    void AddOptions(const vector<Arg>& options);
    bool Parse(span<const char*> args);

    static void ParseArguments(span<const char*> args);

    // If the arg exists returns true and if a value exists for it fill it.
    bool Get(string_view identifier, string& value);
    void PrintHelp() const;
    void PrintUsage() const;

private:
    vector<Arg> options_;
    unordered_map<string, string> abbv_to_full_; // Contains '-' and '--'
    unordered_map<string, string> full_to_value_; // Contains '--'

    string usage_;
    string description_;
    string example_;
    string executable_name_;
};

}  // namespace sc2
