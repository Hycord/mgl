/*
  Map.h
  Created: April 19, 2024
*/

#pragma once
#include <vector>
#include <map>
#include <iterator>

template <class K, class T>
std::pair<std::vector<K>, std::vector<T>> UnpackMap(const std::map<K, T> map)
{
    std::vector<K> keys;
    std::vector<T> values;

    for (auto iterator = map.begin(); iterator != map.end(); ++iterator)
    {
        keys.push_back(iterator->first);
        values.push_back(iterator->second);
    }

    return std::make_pair(keys, values);
};