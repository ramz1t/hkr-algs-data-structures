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

long long fib_const(int n) {
  if (n < 2) return n;

  long long a = 0;
  long long b = 1;
  long long tmp;

  for (int i = 2; i <= n; ++i) {
    tmp = b;
    b = a + b;
    a = tmp;
  }

  return b;
}

int main() {
  int n;
  std::cout << "Enter n: ";
  std::cin >> n;
  std::cout << "Vector fib  " << fib(n) << std::endl;
  std::cout << "Const fib   " << fib_const(n) << std::endl;
  return 0;
}
