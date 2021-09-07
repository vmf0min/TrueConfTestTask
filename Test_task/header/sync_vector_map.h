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

class VectorMap {
 public:
  VectorMap() = delete;
  VectorMap(Vector_t& vec, Map_t& map);
  ~VectorMap() = default;

  auto GetVector() { return vec_; }

  auto GetMap() { return map_; }

 private:
  bool SyncRoutine();

  void RemoveLastVectorElements() {
    std::uniform_int_distribution<int32_t> dist_remove_n_counts(1, 15);
    auto n_count_remove{dist_remove_n_counts(rnd_remove_n_counts_)};
    for (size_t i{}; i < n_count_remove; ++i) vec_.pop_back();
  }

  void RemoveLastMapElements();

 private:
  Vector_t vec_;
  Map_t map_;
  std::random_device rnd_remove_n_counts_;
};

bool VectorMapCheck(Vector_t& vec, Map_t& map);
}  // namespace sync