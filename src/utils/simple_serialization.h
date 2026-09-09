// Simple functions for serializing structures.

#pragma once

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <typeinfo>
#include <vector>

namespace sc2 {
using namespace std;

template <class Stream>
bool IsReading(const Stream& /*stream*/) {
    return typeid(Stream) == typeid(ifstream);
}

// Strings.
static void SerializeT(ifstream& s, string& t) {
    getline(s, t);
}

static void SerializeT(ofstream& s, const string& t) {
    s << t << '\n';
}

// Bools.
static void SerializeT(ifstream& s, bool& t) {
    string linein;
    if (!getline(s, linein)) {
        return;
    }

    t = stoi(linein) == 1;
}

void inline SerializeT(ofstream& s, bool t) {
    if (t) {
        s << "1" << '\n';
    } else {
        s << "0" << '\n';
    }
}

// All other types, assumed to be 32-bit.
template <typename T>
void SerializeT(ifstream& s, T& t) {
    string linein;
    if (!getline(s, linein)) {
        return;
    }

    t = static_cast<T>(stoi(linein));
}

template <typename T>
void SerializeT(ofstream& s, T t) {
    s << to_string(static_cast<uint32_t>(t)) << '\n';
}

static void SerializeT(ofstream& data_file, const set<uint32_t>& s) {
    data_file << to_string(s.size()) << '\n';
    for (auto it : s) {
        data_file << to_string(it) << '\n';
    }
}

static inline void SerializeT(ifstream& data_file, set<uint32_t>& s) {
    uint32_t set_size = 0;
    SerializeT<uint32_t>(data_file, set_size);
    for (uint32_t i = 0; i < set_size; ++i) {
        uint32_t value = 0;
        SerializeT<uint32_t>(data_file, value);
        s.insert(value);
    }
}

}  // namespace sc2
