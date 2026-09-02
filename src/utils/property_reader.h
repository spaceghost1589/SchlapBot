#pragma once

#include <functional>
#include <string>
#include <unordered_map>

namespace sc2 {
using namespace std;

class PropertyReader {
public:
    PropertyReader() = default;
    explicit PropertyReader(const string& file_name);

    [[nodiscard]] bool IsLoaded() const;
    bool LoadFile(const string& file_name);
    void Free();

    // Return false if no properties loaded or value does not exist in file
    bool Read(const string& key, const function<void(const string& v)>& convert);
    bool ReadInt(const string& key, int& value);
    bool ReadFloat(const string& key, float& value);
    bool ReadString(const string& key, string& value);

private:
    unordered_map<string, string> properties_;
    bool file_read_ = false;
};

}  // namespace sc2
