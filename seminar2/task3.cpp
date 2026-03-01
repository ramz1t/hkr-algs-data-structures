#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

using Clock = std::chrono::high_resolution_clock;
using Micros = std::chrono::microseconds;

template <typename Fn>
long long timeUs(Fn fn) {
    auto t0 = Clock::now();
    fn();
    auto t1 = Clock::now();
    return std::chrono::duration_cast<Micros>(t1 - t0).count();
}

int josephusVector(int N, int M) {
    std::vector<int> circle(N);
    for (int i = 0; i < N; ++i) circle[i] = i + 1;

    int current = 0;
    while (circle.size() > 1) {
        current = (current + M) % static_cast<int>(circle.size());
        circle.erase(circle.begin() + current);
        if (current == static_cast<int>(circle.size())) current = 0;
    }
    return circle[0];
}

int josephusVectorIter(int N, int M) {
    std::vector<int> circle(N);
    for (int i = 0; i < N; ++i) circle[i] = i + 1;

    auto it = circle.begin();
    while (circle.size() > 1) {
        for (int i = 0; i < M; ++i) {
            ++it;
            if (it == circle.end()) it = circle.begin();
        }
        it = circle.erase(it);
        if (it == circle.end()) it = circle.begin();
    }
    return circle[0];
}

struct Node {
    int   value;
    Node* prev;
    Node* next;
    explicit Node(int v) : value(v), prev(nullptr), next(nullptr) {}
};

static Node* buildCircle(int N) {
    Node* head = new Node(1);
    Node* cur  = head;
    for (int i = 2; i <= N; ++i) {
        Node* n  = new Node(i);
        n->prev  = cur;
        cur->next = n;
        cur = n;
    }
    cur->next  = head;
    head->prev = cur;
    return head;
}

static Node* removeNode(Node* node) {
    Node* nxt = node->next;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    return nxt;
}

int josephusLinkedList(int N, int M) {
    Node* cur = buildCircle(N);
    int remaining = N;
    while (remaining > 1) {
        for (int i = 0; i < M; ++i) cur = cur->next;
        cur = removeNode(cur);
        --remaining;
    }
    int winner = cur->value;
    delete cur;
    return winner;
}

class CircularListIterator {
public:
    explicit CircularListIterator(Node* start) : current(start) {}

    int value() const { return current->value; }

    CircularListIterator& operator++() {
        current = current->next;
        return *this;
    }

    void remove() {
        current = removeNode(current);
    }

    Node* ptr() const { return current; }

private:
    Node* current;
};

int josephusLinkedListIter(int N, int M) {
    Node* head = buildCircle(N);
    CircularListIterator it(head);
    int remaining = N;
    while (remaining > 1) {
        for (int i = 0; i < M; ++i) ++it;
        it.remove();
        --remaining;
    }
    int winner = it.value();
    delete it.ptr();
    return winner;
}

static void printSeparator() {
    std::cout << std::string(78, '-') << "\n";
}

static void printTableHeader() {
    printSeparator();
    std::cout << std::left
              << std::setw(8)  << "N"
              << std::setw(6)  << "M"
              << std::setw(10) << "Winner"
              << std::setw(14) << "Vec(us)"
              << std::setw(14) << "VecIter(us)"
              << std::setw(14) << "List(us)"
              << std::setw(14) << "ListIter(us)"
              << "\n";
    printSeparator();
}

int main() {
    std::cout << "N=5, M=0 -> eliminated in order, winner=5: "       << josephusVector(5, 0) << "\n";
    std::cout << "N=5, M=1 -> elimination order 2,4,1,5, winner=3: " << josephusVector(5, 1) << "\n";
    std::cout << "All four methods agree for N=7, M=2:\n";
    std::cout << "Vector:       " << josephusVector(7, 2)             << "\n";
    std::cout << "VectorIter:   " << josephusVectorIter(7, 2)         << "\n";
    std::cout << "LinkedList:   " << josephusLinkedList(7, 2)         << "\n";
    std::cout << "LinkedListIt: " << josephusLinkedListIter(7, 2)     << "\n\n";

    printTableHeader();

    std::vector<std::pair<int,int>> testCases = {
        {100,   1},
        {500,   2},
        {1000,  3},
        {3000,  1},
        {5000,  5},
        {10000, 3},
        {20000, 7},
        {50000, 2},
    };

    const int REPS = 10;

    for (auto nm : testCases) {
        int N = nm.first, M = nm.second;
        long long tv = 0, tvi = 0, tl = 0, tli = 0;
        int winner = 0;

        for (int r = 0; r < REPS; ++r) {
            int w;
            tv  += timeUs([&]{ w = josephusVector(N, M); });
            winner = w;
            tvi += timeUs([&]{ josephusVectorIter(N, M); });
            tl  += timeUs([&]{ josephusLinkedList(N, M); });
            tli += timeUs([&]{ josephusLinkedListIter(N, M); });
        }

        std::cout << std::left
                  << std::setw(8)  << N
                  << std::setw(6)  << M
                  << std::setw(10) << winner
                  << std::setw(14) << (tv  / REPS)
                  << std::setw(14) << (tvi / REPS)
                  << std::setw(14) << (tl  / REPS)
                  << std::setw(14) << (tli / REPS)
                  << "\n";
    }
    printSeparator();

    std::cout << "\nVec/VecIter = std::vector; List/ListIter = custom circular doubly-linked list.\n"
              << "All times in microseconds (us), averaged over " << REPS << " runs.\n";

    return 0;
}
