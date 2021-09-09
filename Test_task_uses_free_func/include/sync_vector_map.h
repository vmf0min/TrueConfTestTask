/**
 * @file      sync_vector_map.h
 * @author    vmf0min (vlifom@yandex.ru)
 * @brief     vector and map synchronize class with random removing last
 * elements
 * @version   0.1
 * @date      03-09-2021
 * @copyright Copyright (c) 2021
 */

#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <vector>

namespace sync {
using Vector_t = std::vector<int32_t>;
using Map_t = std::map<int32_t, int64_t>;

bool SyncRoutine(Vector_t& vec, Map_t& map);

void RemoveLastVectorElements(Vector_t& vec);

void RemoveLastMapElements(Map_t& map);

bool VectorMapCheck(Vector_t& vec, Map_t& map);
}  // namespace sync