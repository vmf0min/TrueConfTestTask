/**
 * @file      sync_vector_map.cpp
 * @author    vmf0min (vlifom@yandex.ru)
 * @brief     vector and map synchronize class with random removing last
 * elements
 * @version   0.1
 * @date      03-09-2021
 * @copyright Copyright (c) 2021
 */

#include "../include/sync_vector_map.h"

bool sync::SyncRoutine(Vector_t& vec, Map_t& map) {
  auto iter_last_pos = vec.rbegin();
  for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
    auto find_vec_in_map = map.find(*it);
    if (find_vec_in_map == map.end()) std::swap(*it, *iter_last_pos++);
  }
  vec.resize(vec.size() - (iter_last_pos - vec.rbegin()));

  std::sort(vec.begin(), vec.end());
  std::map<int32_t, int64_t> tmp_map;
  for (auto&& [key_digit, n_digits] : map)
    if (std::binary_search(vec.begin(), vec.end(), key_digit))
      tmp_map[key_digit] = n_digits;
  std::swap(map, tmp_map);

  return sync::VectorMapCheck(vec, map);
}

void sync::RemoveLastMapElements(Map_t& map) {
  std::random_device rnd_remove_n_counts;
  std::uniform_int_distribution<int32_t> dist_remove_n_counts(1, 15);
  auto n_count_remove = dist_remove_n_counts(rnd_remove_n_counts);

  while (n_count_remove) {
    auto last = map.rbegin();
    auto tmp = last->second - n_count_remove;
    if (tmp < 0) {
      n_count_remove -= last->second;
      map.erase(last->first);
    } else {
      last->second = tmp;
      if (last->second == 0) map.erase(last->first);
      n_count_remove = 0;
    }
  }
}

void sync::RemoveLastVectorElements(Vector_t& vec) {
  std::random_device rnd_remove_n_counts;
  std::uniform_int_distribution<int32_t> dist_remove_n_counts(1, 15);
  auto n_count_remove = dist_remove_n_counts(rnd_remove_n_counts);
  for (size_t i = 0; i < n_count_remove; ++i) vec.pop_back();
}

bool sync::VectorMapCheck(Vector_t& vec, Map_t& map) {
  std::set<int32_t> vec_unique_digits;
  for (auto&& i : vec) vec_unique_digits.insert(i);

  std::set<int32_t> map_unique_digits;
  for (auto&& i : map) map_unique_digits.insert(i.first);

  return vec_unique_digits == map_unique_digits;
}