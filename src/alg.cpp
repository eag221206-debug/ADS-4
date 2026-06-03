// Copyright 2021 NNTU-CS
#include <algorithm>
#include <iterator>
#include <cstdint>

int countPairs1(int *arr, int len, int value) {
  int count = 0;
  for (int i = 0; i < len; ++i) {
    for (int j = i + 1; j < len; ++j) {
      if (arr[i] + arr[j] == value) {
        count++;
      } else if (arr[i] + arr[j] > value) {
        break;
      }
    }
  }
  return count;
}

int countPairs2(int *arr, int len, int value) {
  int64_t count = 0;
  for (int i = 0; i < len; ++i) {
    int target = value - arr[i];

    if (target < arr[i]) {
      break;
    }

    auto low = std::lower_bound(arr + i + 1, arr + len, target);

    if (low == arr + len || *low != target) {
      continue;
    }

    auto high = std::upper_bound(low, arr + len, target);

    count += std::distance(low, high);
  }
  return count;
}

int countPairs3(int *arr, int len, int value) {
  int count = 0;
  int left = 0;
  int right = len - 1;

  while (left < right) {
    int sum = arr[left] + arr[right];

    if (sum < value) {
      left++;
    } else if (sum > value) {
      right--;
    } else {
      if (arr[left] != arr[right]) {
        int left_val = arr[left];
        int right_val = arr[right];
        int left_count = 0;
        int right_count = 0;

        while (left < len && arr[left] == left_val) {
          left_count++;
          left++;
        }
        while (right >= 0 && arr[right] == right_val) {
          right_count++;
          right--;
        }
        count += left_count * right_count;
      } else {
        int n = right - left + 1;
        count += static_cast<int64_t>(n) * (n - 1) / 2;
        break;
      }
    }
  }
  return count;
}
