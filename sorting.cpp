#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

void xor_swap(int &x, int &y) {
  if (&x == &y) return;
  x ^= y;
  y ^= x;
  x ^= y;
}

void shuffle_list(std::vector<int> &vec) {
  for (int& x : vec) {
    x = std::rand() % 100 + 1;
  }
}

void print_list(const std::vector<int> &vec) {
  for (int i : vec) std::cout << i << " ";
  std::cout << std::endl;
}

void bubble_sort(std::vector<int> &vec) {
  int n = vec.size();
  for (int i = 0; i < n; ++i) {
    for (int j = 1; j < n; ++j) {
      if (vec[j] < vec[j - 1])
        xor_swap(vec[j], vec[j - 1]);
    }
  }
}

void selection_sort(std::vector<int> &vec) {
  int n = vec.size();
  for (int i = 0; i < n; ++i) {
    int minI = i;
    for (int j = i; j < n; ++j) {
      if (vec[j] < vec[minI]) minI = j;
    }
    xor_swap(vec[i], vec[minI]);
  }
}


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

void merge_sort(std::vector<int> &vec) {

}

int main() {
  std::vector<int> vec(20);
  std::srand(std::time(nullptr));

  std::cout << "--- Bubble sort ---" << std::endl;
  shuffle_list(vec);
  print_list(vec);
  bubble_sort(vec);
  print_list(vec);

  std::cout << "--- Selection sort ---" << std::endl;
  shuffle_list(vec);
  print_list(vec);
  selection_sort(vec);
  print_list(vec);

  std::cout << "--- Insertion sort ---" << std::endl;
  shuffle_list(vec);
  print_list(vec);
  insertion_sort(vec);
  print_list(vec);

  std::cout << "--- Merge sort ---" << std::endl;
  shuffle_list(vec);
  print_list(vec);
  merge_sort(vec);
  print_list(vec);

  return 0;
}
