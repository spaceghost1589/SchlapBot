#pragma once

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <span>
#include <string>
#include <utility>

#include "arg_parser.h"
#include "lib/game_settings.h"

namespace sc2 {

using std::cout,
	std::cerr,
	std::int8_t,
    std::int32_t,
	std::ranges::all_of,
	std::ranges::find_if,
    std::span,
    std::string,
    std::string_view,
    std::stoi,
    std::vector;


// ArgParser::ArgParser(const string& executable_name) : executable_name_(executable_name)
ArgParser::ArgParser(const string_view executable_name) : executable_name_(executable_name) {
}

ArgParser::ArgParser(string usage,
                     string description,
                     string example)
    : usage_(std::move(usage)),
      description_(std::move(description)),
      example_(std::move(example)) {
}

void ArgParser::ParseArguments(span<char*> args)
{
    // executable_name
    ArgParser arg_parser(string_view(args.front()));

    arg_parser.AddOptions(
        {
            {.abbreviation_="-g", .fullname_="--GamePort", .description_="Port of client to connect to", .required_=false},
            {.abbreviation_="-o", .fullname_="--StartPort", .description_="Starting server port", .required_=false},
            {.abbreviation_="-l", .fullname_="--LadderServer", .description_="Ladder server address", .required_=false},
            {.abbreviation_="-x", .fullname_="--OpponentId", .description_="PlayerId of opponent", .required_=false},
        }
    );

    arg_parser.Parse(args);

    LadderSettings ladder_settings;

    if (string GamePortStr; arg_parser.Get("GamePort", GamePortStr)) {
        ladder_settings.game_port = stoi(GamePortStr);
    }

    if (string StartPortStr; arg_parser.Get("StartPort", StartPortStr)) {
        ladder_settings.start_port = stoi(StartPortStr);
    }

    if (string OpponentId; arg_parser.Get("OpponentId", OpponentId)) {
        ladder_settings.opponent_id = OpponentId;
    }

    arg_parser.Get("LadderServer", ladder_settings.ladder_server);
} // ParseArguments

//! Adds options (`Arg`) to `options_` vector.
//! @param options const vector<Arg>&
void ArgParser::AddOptions(const vector<Arg>& options) {
    for (const Arg& opt : options) {
        options_.push_back(opt);
        abbv_to_full_[opt.abbreviation_] = opt.fullname_;
    }
} // AddOptions

//! @return false if `args is empty`, invalid option, or help command
bool ArgParser::Parse(span<char*> args) {
	if (args.empty()) {
		return false;
	}

	// Capture the executable name.
	executable_name_ = args[0];

	// Start at 1 to skip the executable name.
	for (size_t i = 1; i < args.size(); ++i) {
		string_view arg = args[i];

		// Skip values.
		if (arg.empty() || arg.front() != '-') {
			continue;
		}

		if (arg == "--help" || arg == "-h") {
			PrintHelp();
			return false;
		}

		// Check if it's a valid option.
		auto it = find_if(options_, [&](const Arg& option) {
			return option.abbreviation_ == arg || option.fullname_ == arg;
		});
		// `find_if` returns `size() + 1` if it fails to find anything.
		if (it == options_.end()) {
			std::cerr << arg << " is an unrecognized argument.\n";
			return false;
		}

		// Resolve fullname from abbreviation
		string fullname;
		if (arg.size() > 1 && arg[1] != '-') {
			fullname = abbv_to_full_[string(arg)];
		} else {
			fullname = string(arg);
		}

		// Look one ahead for the value
		string_view value;
		if (i + 1 < args.size()) {
			if (string_view next_arg = args[i + 1]; !next_arg.empty() && next_arg.front() != '-') {
				value = next_arg;
				++i; // Advance the iterator past the value
			}
		}

		// Remove leading '--' and save to map
		fullname.erase(0, 2);
		full_to_value_[fullname] = std::string(value);
	}

	// Verify all required arguments exist
	return all_of(options_, [&](const Arg& option) {
		if (!option.required_) {
			return true;
		}

		const string key = option.fullname_.substr(2); // Get name without '--'

		// C++20 .contains() is safer than .at() and doesn't throw
		return full_to_value_.contains(key);
	});
} // Parse

bool ArgParser::Get(const string& identifier, string& value) {
    string fullname = identifier;

    // If the identifier is the abbreviation turn it into the fullname
    if (fullname.size() == 1) {
        const auto identifier_ = abbv_to_full_.find("-" + identifier);

        if (identifier_ == abbv_to_full_.end()) {
            return false;
        }

        fullname = identifier_->second;
    }

    if (fullname.front() == '-') {
        fullname.erase(0, 2);
    }

    const auto it = full_to_value_.find(fullname);

    if (it == full_to_value_.end()) {
        return false;
    }

    value = it->second;

    return true;
} // Get

void ArgParser::PrintHelp() const {
    PrintUsage();
    cout << "Options -" << '\n';
    for (const Arg& opt : options_) {
        cout << "  " << opt.abbreviation_ << ", " << opt.fullname_ << " " << opt.description_ << '\n';
    }
} // PrintHelp

void ArgParser::PrintUsage() const {
    cout << "Usage: " << executable_name_ << " ";
    // Append required arguments.
    for (const Arg& opt : options_) {
        if (opt.required_) {
            string fullname = opt.fullname_;
            fullname.erase(0, 2);
            cout << opt.abbreviation_ << " [" << fullname << "] ";
        }
    }
    cout << '\n' << '\n';
} // PrintUsage

} // namespace sc2
