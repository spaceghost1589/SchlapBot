#pragma once

#include <cstdint>
#include <string>
#include <vector>

using std::string,
    std::vector;

namespace sc2 {

bool DoesFileExist(const string& path);
bool HasExtension(const string& path, const string& extension);
uint64_t StartProcess(const string& process_path, const vector<string>& command_line);
bool IsProcessRunning(uint64_t process_id);
bool TerminateProcess(uint64_t process_id);
bool IsInDebugger();
void SleepFor(unsigned int ms);
bool PollKeyPress();
string GetUserDirectory();
string GetLibraryMapsDirectory();
string GetGameMapsDirectory(const string& process_path);

bool FindLatestExe(string& path);
bool FindBaseExe(string& path, uint32_t base_build);

}  // namespace sc2
