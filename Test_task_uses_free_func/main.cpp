/**
 * @file      main.cpp
 * @author    vmf0min (vlifom@yandex.ru)
 * @brief     Test task
 * 1.заполнить случайными числами от 1 до 9 значения контейнеров vector[i] и
 * map[i];
 * 2.удалить случайное число элементов (не более 15) в каждом контейнере;
 * 3.после этого провести синхронизацию, чтобы в vector и map остались
 * только имеющиеся в обоих контейнерах элементы (дубликаты не удалять).
 * @version   0.1
 * @date      03-09-2021
 * @copyright Copyright (c) 2021
 */

#include "include/sync_vector_map.h"

bool TestSyncVectorMap() {
  bool is_sync = true;
  std::random_device rnd_plane_digits;
  std::uniform_int_distribution<int32_t> dist_plane_digits(1, 9);

  std::random_device rnd_size;
  std::uniform_int_distribution<size_t> dist_rnd_size(15, 1000);

  const size_t test_loops = 1000;
  std::vector<bool> checks(test_loops);
  for (size_t test_step = 0; test_step < test_loops; ++test_step) {
    std::vector<int32_t> vec(dist_rnd_size(rnd_size));
    for (auto&& value : vec) value = dist_plane_digits(rnd_plane_digits);
    sync::RemoveLastVectorElements(vec);

    std::map<int32_t, int64_t> map;
    for (size_t cnt = 0; cnt < dist_rnd_size(rnd_size); ++cnt)
      ++map[(dist_plane_digits(rnd_plane_digits))];
    sync::RemoveLastMapElements(map);

    while (!sync::SyncRoutine(vec, map)) {
    }
    checks[test_step] = sync::VectorMapCheck(vec, map);
  }

  for (auto&& i : checks) is_sync &= i;
  return is_sync;
}

int main() {
  system("cls");

  std::cout << "vector and map are";
  std::cout << (TestSyncVectorMap() ? "\x1b[32m synchronized"
                                    : "\x1b[31m not synchronized");
  std::cout << "\x1b[0m" << std::endl;
}