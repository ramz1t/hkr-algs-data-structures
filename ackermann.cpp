#include <iostream>
#include <cmath>

int ack(int i, int j) {
  if (i == 1 && j >= 1) return pow(2, j);
  else if (i > 1 && j == 1) return ack(i - 1, 2);
  else return ack(i - 1, ack(i, j - 1));
}

int main() {
  std::cout << ack(1, 2) << std::endl;
  std::cout << ack(2, 1) << std::endl;
  std::cout << ack(2, 2) << std::endl;
  return 0;
}
