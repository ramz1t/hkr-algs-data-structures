#include <iostream>
#include <vector>

long long fib(int n) {
  std::vector<long long> vec(n + 1);
  
  vec[0] = 0;
  vec[1] = 1;

  for (int i = 2; i <= n; ++i) {
    vec[i] = vec[i - 1] + vec[i - 2];
  }

  return vec[n];
}

int main() {
  int n;
  std::cout << "Enter n: ";
  std::cin >> n;
  std::cout << fib(n);
  return 0;
}
