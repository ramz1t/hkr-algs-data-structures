#include <iostream>

void hanoi(int n, char from, char to, char temp) {
  if (n == 0) return;

  hanoi(n - 1, from, temp, to);

  std::cout << "Moving disk " << n << " from " << from << " to " << to << std::endl;

  hanoi(n - 1, temp, to, from);
}

int main() {
  hanoi(3, 'A', 'C', 'B');
  return 0;
}
