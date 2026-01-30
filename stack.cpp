#include <iostream>
#include <stdexcept>

template <typename T>
class Node {
public:
  T value;
  Node* next;

  Node(const T& v, Node* n = nullptr) : value(v), next(n) {}
};

template <typename T>
class Stack {
private:
  Node<T>* top;
  std::size_t count;

public:
  Stack() : top(nullptr), count(0) {}

  void push(const T& v) {
    top = new Node<T>(v, top);
    count++;
  }

  T pop() {
    if (!top) {
      throw std::runtime_error("Stack is empty");
    }
    int val = top->value;
    Node<T>* old = top;
    top = top->next;
    delete old;
    count--;
    return val;
  }

  std::size_t size() const {
    return count;
  }
};

int main() {
  Stack<int> stack;
  stack.push(10);
  stack.push(20);
  stack.push(30);
  std::cout << "Size " << stack.size() << std::endl;
  std::cout << stack.pop() << std::endl;
  std::cout << stack.pop() << std::endl;
  std::cout << stack.pop() << std::endl;
  std::cout << "Size " << stack.size() << std::endl;
}
