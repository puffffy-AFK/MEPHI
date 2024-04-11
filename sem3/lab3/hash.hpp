#pragma once

#include <string>
#include <type_traits>

template <typename K>
struct MyHash;


template <>
struct MyHash<std::string> {
    size_t operator()(const std::string& key) const {
        size_t hash = 0;
        for (char c : key) {
            hash = (hash * 131) + c;
        }
        return hash;
    }
};


template <typename K>
struct MyHash {
    size_t operator()(const K& key) const {
        if constexpr (std::is_floating_point_v<K>) {
            auto key_cast = reinterpret_cast<const char*>(&key);
            return MyHash<std::string>{}(std::string(key_cast, key_cast + sizeof(K)));
        } else {
            return key ^ (key >> 3);
        }
    }
};
