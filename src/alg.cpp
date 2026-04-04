// Copyright 2021 NNTU-CS

int countEqualInRange(int *arr, int L, int R, int target) {
    if (L > R) return 0;

    // Первый индекс >= target
    int left = L, right = R, first = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] >= target) {
            first = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    if (first == -1 || arr[first] != target) return 0;

    // Первый индекс > target
    left = first;
    right = R;
    int last = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > target) {
            last = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    int upper = (last == -1 ? R + 1 : last);
    return upper - first;
}

int countPairs1(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (arr[i] + arr[j] == value) {
                count++;
            }
        }
    }
    return count;
}

int countPairs2(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        int target = value - arr[i];
        count += countEqualInRange(arr, i + 1, len - 1, target);
    }
    return count;
}

int countPairs3(int *arr, int len, int value) {
  int count = 0;
    int left = 0;
    int right = len - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == value) {
            int l_val = arr[left];
            int r_val = arr[right];
            if (l_val == r_val) {
                int num = right - left + 1;
                count += num * (num - 1) / 2;
                break;
            } else {
                int l_count = 0;
                while (left < right && arr[left] == l_val) {
                    l_count++;
                    left++;
                }
                int r_count = 0;
                int r_idx = right;
                while (r_idx >= left && arr[r_idx] == r_val) {
                    r_count++;
                    r_idx--;
                }
                count += l_count * r_count;
                right = r_idx;
            }
        } else if (sum < value) {
            left++;
        } else {
            right--;
        }
    }
    return count;
}
