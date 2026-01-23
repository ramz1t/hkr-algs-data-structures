#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

int main() {
  int size = 2000000;
  std::vector<bool> isPrime(size, true);
  
  isPrime[0] = false;
  isPrime[1] = false;

  int limit = static_cast<int>(std::sqrt(size));
  for (int i = 2; i < limit; ++i) {
    if (isPrime[i]) {
      for (int j = i * i; j < size; j += i) {
        isPrime[j] = false;
      }
    }
  }

  long long sum = 0;
  for (int i = 2; i < size; ++i) {
    if (isPrime[i]) sum += i;
  }

  std::cout << sum;

  return 0;
}
