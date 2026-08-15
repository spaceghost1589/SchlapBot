module;
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include "dirent.h"
#else
#include <dirent.h>
#endif
export module sc2_scan_directory;


export namespace sc2 {

using std::string,
    std::vector;

int scan_directory(const char* directory_path, vector <string>& files, bool full_path, bool list_directories) {
    if (!directory_path || !*directory_path) {
        return 0;
    }

    DIR* dir = opendir(directory_path);
    if (!dir) {
        return 0;
    }

    dirent* ent;

    while ((ent = readdir(dir)) != nullptr) {
        switch (ent->d_type) {
            case DT_REG: {
                if (list_directories) {
                    continue;
                }

                if (!full_path) {
                    files.push_back(ent->d_name);
                } else {
                    files.push_back(string(directory_path) + string(ent->d_name));
                }
            }
            case DT_DIR: {
                if (!list_directories || !*ent->d_name) {
                    continue;
                }

                if (std::strcmp(ent->d_name, ".") == 0 || std::strcmp(ent->d_name, "..") == 0) {
                    continue;
                }

                if (!full_path) {
                    files.push_back(ent->d_name);
                } else {
                    files.push_back(string(directory_path) + string(ent->d_name));
                }
            } break;
        }
    }

    return static_cast<int>(files.size());
}

}  // namespace sc2
