/**
 * @file      sync_vector_map.cpp
 * @author    vmf0min (vlifom@yandex.ru)
 * @brief     vector and map_in synchronize class
 * @version   0.1
 * @date      03-09-2021
 * @copyright Copyright (c) 2021
 */

#include "../header/sync_vector_map.h"

bool sync::VectorMap::SyncRoutine() {
  auto iter_out{vec_.rbegin()};
  for (auto it{vec_.rbegin()}; it != vec_.rend(); ++it) {
    auto iter{map_.find(*it)};
    if (iter == map_.end()) std::swap(*it, *(iter_out++));
  }
  vec_.resize(vec_.size() - (iter_out - vec_.rbegin()));

  std::sort(vec_.begin(), vec_.end());
  std::map<int32_t, int64_t> new_map;
  for (auto&& [key_digit, n_digits] : map_)
    if (std::binary_search(vec_.begin(), vec_.end(), key_digit))
      new_map[key_digit] = n_digits;
  map_ = std::move(new_map);

  return sync::VectorMapCheck(vec_, map_);
}

void sync::VectorMap::RemoveLastMapElements() {
  std::uniform_int_distribution<int32_t> dist_remove_n_counts(1, 15);
  auto n_count_remove{dist_remove_n_counts(rnd_remove_n_counts_)};

  while (n_count_remove) {
    auto last{map_.rbegin()};
    auto tmp{last->second - n_count_remove};
    if (tmp < 0) {
      n_count_remove -= last->second;
      map_.erase(last->first);
    } else {
      last->second = tmp;
      if (last->second == 0) map_.erase(last->first);
      n_count_remove = 0;
    }
  }
}

bool sync::VectorMapCheck(std::vector<int32_t>& vec,
                          std::map<int32_t, int64_t>& map) {
  std::set<int32_t> vec_unique_digits;
  for (auto&& i : vec) vec_unique_digits.insert(i);

  std::set<int32_t> map_unique_digits;
  for (auto&& i : map) map_unique_digits.insert(i.first);

  return vec_unique_digits == map_unique_digits;
}