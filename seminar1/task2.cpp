#include "timer.hpp"
#include <vector>
#include <fstream>
#include <iostream>

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

bool binary_search_rec(const std::vector<int>& a, int left, int right, int target) {
  if (left > right)
    return false;

  int mid = left + (right - left) / 2;

  if (a[mid] == target)
    return true;
  if (target < a[mid])
    return binary_search_rec(a, left, mid - 1, target);
  else
    return binary_search_rec(a, mid + 1, right, target);
}

bool binary_search(const std::vector<int>& a, int target) {
  return binary_search_rec(a, 0, a.size() - 1, target);
}

void merge(std::vector<int> &vec, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  std::vector<int> l(n1), r(n2);

  for (int i = 0; i < n1; ++i)
    l[i] = vec[left + i];
  for (int j = 0; j < n2; ++j)
    r[j] = vec[mid + j + 1];

  int i = 0, j = 0, k = left;

  while (i < n1 && j < n2) {
    if (l[i] <= r[j]) {
      vec[k] = l[i];
      i++;
    } else {
      vec[k] = r[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    vec[k] = l[i];
    i++;
    k++;
  }

  while (j < n2) {
    vec[k] = r[j];
    j++;
    k++;
  }
}

void merge_sort(std::vector<int> &vec, int left, int right) {
  if (left >= right) return;
  
  int mid = left + (right - left) / 2;
  merge_sort(vec, left, mid);
  merge_sort(vec, mid + 1, right);
  merge(vec, left, mid, right);
}

void run_test(int n, int repeats) {
  std::vector<int> data = load_from_file(FILE, n);
  merge_sort(data, 0, data.size() - 1);

  Timer timer;
  double total_time = 0.0;
  volatile bool found;

  int target = data[0];

  for (int i = 0; i < repeats; ++i) {
    timer.begin();
    found = binary_search(data, target);
    timer.stop();
    total_time += timer.time_ns();
  }

  std::cout << "Binary search (" << n << ") " << total_time  / repeats << " ns\n";
}

int main() {
  int repeats = 100000;
  int sizes[] = {100, 1000, 10000, 100000, 1000000};

  for (int n : sizes) {
    run_test(n, repeats);
  }

  return 0;
}