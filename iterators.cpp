#include <iostream>
#include <vector>
#include <string>

int main() {
  std::vector<std::string> vec = {"first", "second", "third"};
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    std::cout << *it << "\n";
  }
  return 0;
}
