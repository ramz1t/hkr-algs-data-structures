#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <functional>

#define FILE "numbers.txt"

// Used to measure sorting time
class Timer {
public:
  using clock = std::chrono::high_resolution_clock;

  void begin() {
    start = clock::now();
  }

  void stop() {
    end = clock::now();
  }

  double time_ms() const {
    return std::chrono::duration<double, std::milli>(end - start).count();
  }

private:
  clock::time_point start;
  clock::time_point end;
};

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

// Swaps two variables
void xor_swap(int &x, int &y) {
  if (&x == &y) return;
  x ^= y;
  y ^= x;
  x ^= y;
}

// Rearranges elements around a pivot
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

// Median of three values
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

// Pivot = median of three elements
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

// Runs sort_method on n elements and logs time
void run_test(int n, const std::string& name, std::function<void(std::vector<int>&)> sort_method) {
  Timer timer;
  std::vector<int> nums = load_from_file(FILE, n);

  timer.begin();
  sort_method(nums);
  timer.stop();

  std::cout << name << " (" << n << ") " << timer.time_ms() << " ms\n";
}

int main() {
  int n = 5;
  int sizes[5] = {100, 1000, 10000, 100000, 1000000};

  for (size_t size : sizes) 
    run_test(size, "Quick m3", quick_sort_m3);

  std::cout << "--------------------------\n";
  for (size_t size : sizes) 
    run_test(size, "Quick rand", quick_sort_rand);
    
  std::cout << "--------------------------\n";
  for (size_t size : sizes) 
    run_test(size, "Quick start", quick_sort_start);

  std::cout << "--------------------------\n";
  for (size_t size : sizes) 
    run_test(size, "Insertion", insertion_sort);

  return 0;
}

/*
--- RESULT ---
Quick m3 (100) 0.007667 ms
Quick m3 (1000) 0.107916 ms
Quick m3 (10000) 3.26421 ms
Quick m3 (100000) 246.95 ms
Quick m3 (1000000) 23729.5 ms
--------------------------
Quick rand (100) 0.007292 ms
Quick rand (1000) 0.101208 ms
Quick rand (10000) 3.24538 ms
Quick rand (100000) 245.018 ms
Quick rand (1000000) 23918.7 ms
--------------------------
Quick start (100) 0.007417 ms
Quick start (1000) 0.091709 ms
Quick start (10000) 3.19558 ms
Quick start (100000) 242.713 ms
Quick start (1000000) 23968.7 ms
--------------------------
Insertion (100) 0.010583 ms
Insertion (1000) 0.85275 ms
Insertion (10000) 87.6417 ms
Insertion (100000) 8720.32 ms
Insertion (1000000) 894376 ms
*/