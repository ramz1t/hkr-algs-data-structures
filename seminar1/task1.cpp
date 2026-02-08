#include <iostream>
#include <vector>
#include <fstream>
#include <functional>
#include <utility>
#include <cstdlib>
#include "timer.hpp"

#define FILE "numbers.txt"

// Reads n numbers from given file
std::vector<int> load_from_file(const std::string &filename, int n) {
  std::ifstream file(filename);
  std::vector<int> result;

  int x;
  while (result.size() < n && file >> x) {
    result.push_back(x);
  }

  return result;
}

// Iterative insertion sort
void insertion_sort(std::vector<int> &vec) {
  int n = vec.size();
  for (int i = 1; i < n; ++i) {
    int key = vec[i];
    int j = i - 1;
    while (j >= 0 && vec[j] > key) {
      vec[j + 1] = vec[j];
      --j;
    }
    vec[j + 1] = key;
  }
}

// Recursive insertion sort
void insertion_sort_rec_impl(std::vector<int>& a, int n) {
  if (n <= 1) return;

  insertion_sort_rec_impl(a, n - 1);

  int key = a[n - 1];
  int j = n - 2;
  while (j >= 0 && a[j] > key) {
    a[j + 1] = a[j];
    --j;
  }
  a[j + 1] = key;
}

void insertion_sort_rec(std::vector<int>& vec) {
  insertion_sort_rec_impl(vec, vec.size());
}

void xor_swap(int &x, int &y) {
  if (&x == &y) return;
  x ^= y;
  y ^= x;
  x ^= y;
}

int partition(std::vector<int>& a, int low, int high, int pivotIndex) {
  xor_swap(a[pivotIndex], a[high]);
  int pivot = a[high];
  int i = low - 1;

  for (int j = low; j < high; ++j) {
    if (a[j] <= pivot) {
      ++i;
      xor_swap(a[i], a[j]);
    }
  }
  xor_swap(a[i + 1], a[high]);
  return i + 1;
}

int median_of_three(std::vector<int>& a, int low, int high) {
  int mid = (low + high) / 2;

  if (a[low] > a[mid])  xor_swap(a[low], a[mid]);
  if (a[low] > a[high]) xor_swap(a[low], a[high]);
  if (a[mid] > a[high]) xor_swap(a[mid], a[high]);

  return mid;
}

// Pivot = first element
void quick_sort_start_rec(std::vector<int>& a, int low, int high) {
  if (low < high) {
    int p = partition(a, low, high, low);
    quick_sort_start_rec(a, low, p - 1);
    quick_sort_start_rec(a, p + 1, high);
  }
}

void quick_sort_start(std::vector<int>& vec) {
  quick_sort_start_rec(vec, 0, vec.size() - 1);
}

// Pivot = random element
void quick_sort_rand_rec(std::vector<int>& a, int low, int high) {
  if (low < high) {
    int pivotIndex = low + rand() % (high - low + 1);
    int p = partition(a, low, high, pivotIndex);
    quick_sort_rand_rec(a, low, p - 1);
    quick_sort_rand_rec(a, p + 1, high);
  }
}

void quick_sort_rand(std::vector<int>& vec) {
  quick_sort_rand_rec(vec, 0, vec.size() - 1);
}

// Pivot = median of three
void quick_sort_m3_rec(std::vector<int>& a, int low, int high) {
  if (low < high) {
    int pivotIndex = median_of_three(a, low, high);
    int p = partition(a, low, high, pivotIndex);
    quick_sort_m3_rec(a, low, p - 1);
    quick_sort_m3_rec(a, p + 1, high);
  }
}

void quick_sort_m3(std::vector<int>& vec) {
  quick_sort_m3_rec(vec, 0, vec.size() - 1);
}

using PivotFunc = std::function<int(std::vector<int>&, int, int)>;

void quick_sort_iter(std::vector<int>& a, PivotFunc pickPivot) {
  std::vector<std::pair<int,int>> stack;
  stack.push_back({0, (int)a.size() - 1});

  while (!stack.empty()) {
    auto [low, high] = stack.back();
    stack.pop_back();

    if (low < high) {
      int pivotIndex = pickPivot(a, low, high);
      int p = partition(a, low, high, pivotIndex);

      stack.push_back({low, p - 1});
      stack.push_back({p + 1, high});
    }
  }
}

int pivot_start(std::vector<int>&, int low, int) {
  return low;
}

int pivot_rand(std::vector<int>&, int low, int high) {
  return low + rand() % (high - low + 1);
}

int pivot_m3(std::vector<int>& a, int low, int high) {
  return median_of_three(a, low, high);
}

void quick_sort_start_iter(std::vector<int>& vec) {
  quick_sort_iter(vec, pivot_start);
}

void quick_sort_rand_iter(std::vector<int>& vec) {
  quick_sort_iter(vec, pivot_rand);
}

void quick_sort_m3_iter(std::vector<int>& vec) {
  quick_sort_iter(vec, pivot_m3);
}

using SortFunc = std::function<void(std::vector<int>&)>;

void run_test(int n, int repeats, const std::string& name, SortFunc sort_method) {
  Timer timer;
  double total_time = 0.0;
  std::vector<int> original = load_from_file(FILE, n);

  for (int i = 0; i < repeats; ++i) {
    std::vector<int> nums = original;
    timer.begin();
    sort_method(nums);
    timer.stop();
    total_time += timer.time_ms();
  }

  std::cout << name << " (" << n << ") " << total_time / repeats << " ms\n";
}

int main() {
  int repeats = 5;
  int sizes[5] = {100, 1000, 10000, 100000, 1000000};

  for (int size : sizes) {
    run_test(size, repeats, "Quick start rec", quick_sort_start);
    run_test(size, repeats, "Quick start iter", quick_sort_start_iter);
    run_test(size, repeats, "Quick rand rec", quick_sort_rand);
    run_test(size, repeats, "Quick rand iter", quick_sort_rand_iter);
    run_test(size, repeats, "Quick m3 rec", quick_sort_m3);
    run_test(size, repeats, "Quick m3 iter", quick_sort_m3_iter);
    run_test(size, repeats, "Insertion iter", insertion_sort);
    run_test(size, repeats, "Insertion rec", insertion_sort_rec);
    std::cout << "--------------------------\n";
  }

  return 0;
}