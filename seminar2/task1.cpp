#include <iostream>
#include <stack>
#include <queue>
#include <stdexcept>
#include <string>

static constexpr int MAX_SIZE = 1024;

// a) Queue using two stacks
template <typename T>
class QueueTwoStacks {
public:
    void enqueue(const T& val) {
        if (inbox.size() + outbox.size() >= MAX_SIZE) {
            std::cerr << "[QueueTwoStacks] OVERFLOW: queue is full (max " << MAX_SIZE << ")\n";
            return;
        }
        inbox.push(val);
    }

    T dequeue() {
        if (inbox.empty() && outbox.empty()) {
            std::cerr << "[QueueTwoStacks] UNDERFLOW: queue is empty\n";
            throw std::underflow_error("QueueTwoStacks: underflow");
        }
        if (outbox.empty()) {
            while (!inbox.empty()) {
                outbox.push(inbox.top());
                inbox.pop();
            }
        }
        T val = outbox.top();
        outbox.pop();
        return val;
    }

    bool empty() const { return inbox.empty() && outbox.empty(); }
    int  size()  const { return static_cast<int>(inbox.size() + outbox.size()); }

private:
    std::stack<T> inbox;
    std::stack<T> outbox;
};

// b) Queue using one stack
template <typename T>
class QueueOneStack {
public:
    void enqueue(const T& val) {
        if (stk.size() >= MAX_SIZE) {
            std::cerr << "[QueueOneStack] OVERFLOW: queue is full (max " << MAX_SIZE << ")\n";
            return;
        }
        stk.push(val);
    }

    T dequeue() {
        if (stk.empty()) {
            std::cerr << "[QueueOneStack] UNDERFLOW: queue is empty\n";
            throw std::underflow_error("QueueOneStack: underflow");
        }
        return popBottom(stk);
    }

    bool empty() const { return stk.empty(); }
    int  size()  const { return static_cast<int>(stk.size()); }

private:
    static T popBottom(std::stack<T>& s) {
        T top = s.top();
        s.pop();
        if (s.empty()) return top;
        T bottom = popBottom(s);
        s.push(top);
        return bottom;
    }

    std::stack<T> stk;
};

// c) Stack using two queues
template <typename T>
class StackTwoQueues {
public:
    void push(const T& val) {
        if (q1.size() >= MAX_SIZE) {
            std::cerr << "[StackTwoQueues] OVERFLOW: stack is full (max " << MAX_SIZE << ")\n";
            return;
        }
        q2.push(val);
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        std::swap(q1, q2);
    }

    T pop() {
        if (q1.empty()) {
            std::cerr << "[StackTwoQueues] UNDERFLOW: stack is empty\n";
            throw std::underflow_error("StackTwoQueues: underflow");
        }
        T val = q1.front();
        q1.pop();
        return val;
    }

    T top() const {
        if (q1.empty()) {
            std::cerr << "[StackTwoQueues] UNDERFLOW: stack is empty\n";
            throw std::underflow_error("StackTwoQueues: underflow");
        }
        return q1.front();
    }

    bool empty() const { return q1.empty(); }
    int  size()  const { return static_cast<int>(q1.size()); }

private:
    std::queue<T> q1;
    std::queue<T> q2;
};

// d) Stack using one queue
template <typename T>
class StackOneQueue {
public:
    void push(const T& val) {
        if (q.size() >= MAX_SIZE) {
            std::cerr << "[StackOneQueue] OVERFLOW: stack is full (max " << MAX_SIZE << ")\n";
            return;
        }
        q.push(val);
        for (int i = 0; i < static_cast<int>(q.size()) - 1; ++i) {
            q.push(q.front());
            q.pop();
        }
    }

    T pop() {
        if (q.empty()) {
            std::cerr << "[StackOneQueue] UNDERFLOW: stack is empty\n";
            throw std::underflow_error("StackOneQueue: underflow");
        }
        T val = q.front();
        q.pop();
        return val;
    }

    T top() const {
        if (q.empty()) {
            std::cerr << "[StackOneQueue] UNDERFLOW: stack is empty\n";
            throw std::underflow_error("StackOneQueue: underflow");
        }
        return q.front();
    }

    bool empty() const { return q.empty(); }
    int  size()  const { return static_cast<int>(q.size()); }

private:
    std::queue<T> q;
};

static void separator(const std::string& title) {
    std::cout << "\n===== " << title << " =====\n";
}

template <typename Queue>
void testQueue(const std::string& label) {
    separator(label);
    Queue q;
    for (int i = 1; i <= 5; ++i) {
        q.enqueue(i);
        std::cout << "Enqueued: " << i << "\n";
    }
    std::cout << "Dequeue order (expect 1..5): ";
    while (!q.empty()) std::cout << q.dequeue() << " ";
    std::cout << "\n";
    std::cout << "Trying to dequeue from empty queue:\n";
    try { q.dequeue(); } catch (...) {}
}

template <typename Stack>
void testStack(const std::string& label) {
    separator(label);
    Stack s;
    for (int i = 1; i <= 5; ++i) {
        s.push(i);
        std::cout << "Pushed: " << i << "\n";
    }
    std::cout << "Pop order (expect 5..1): ";
    while (!s.empty()) std::cout << s.pop() << " ";
    std::cout << "\n";
    std::cout << "Trying to pop from empty stack:\n";
    try { s.pop(); } catch (...) {}
}

template <typename Queue>
void testOverflow(const std::string& label) {
    separator(label);
    Queue q;
    for (int i = 0; i <= MAX_SIZE; ++i) q.enqueue(i);
    std::cout << "Queue size after overflow attempt: " << q.size() << "\n";
}

int main() {
    testQueue<QueueTwoStacks<int>>  ("a) Queue using two stacks");
    testQueue<QueueOneStack<int>>   ("b) Queue using one stack");
    testStack<StackTwoQueues<int>>  ("c) Stack using two queues");
    testStack<StackOneQueue<int>>   ("d) Stack using one queue");
    testOverflow<QueueTwoStacks<int>>("Overflow test (capacity " + std::to_string(MAX_SIZE) + ")");
    return 0;
}
