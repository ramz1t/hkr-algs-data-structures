#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace chrono;

class BinaryHeap {
    vector<int> data;

    void siftUp(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (data[p] > data[i]) { swap(data[p], data[i]); i = p; }
            else break;
        }
    }

    void siftDown(int i, int n) {
        while (true) {
            int s = i, l = 2*i+1, r = 2*i+2;
            if (l < n && data[l] < data[s]) s = l;
            if (r < n && data[r] < data[s]) s = r;
            if (s == i) break;
            swap(data[i], data[s]); i = s;
        }
    }

public:
    // Algorithm 1: successive inserts, O(n log n)
    void insert(int val) {
        data.push_back(val);
        siftUp(size() - 1);
    }

    // Algorithm 2: linear-time build, O(n)
    void build(vector<int> arr) {
        data = arr;
        int s = size();
        for (int i = s/2 - 1; i >= 0; i--)
            siftDown(i, s);
    }

    int deleteMin() {
        int m = data[0];
        data[0] = data.back(); data.pop_back();
        if (!data.empty()) siftDown(0, size());
        return m;
    }

    void print() const {
        cout << "[ ";
        for (int x : data) cout << x << " ";
        cout << "]\n";
    }

    void inOrder(int i, int n) const {
        if (i >= n) return;
        inOrder(2*i+1, n); cout << data[i] << " "; inOrder(2*i+2, n);
    }
    void preOrder(int i, int n) const {
        if (i >= n) return;
        cout << data[i] << " "; preOrder(2*i+1, n); preOrder(2*i+2, n);
    }
    void postOrder(int i, int n) const {
        if (i >= n) return;
        postOrder(2*i+1, n); postOrder(2*i+2, n); cout << data[i] << " ";
    }
    void levelOrder() const { for (int x : data) cout << x << " "; }

    void printTraversals() const {
        int n = size();
        cout << "  In-order:    "; inOrder(0, n);    cout << "\n";
        cout << "  Pre-order:   "; preOrder(0, n);   cout << "\n";
        cout << "  Post-order:  "; postOrder(0, n);  cout << "\n";
        cout << "  Level-order: "; levelOrder();     cout << "\n";
    }

    int size() const { return (int)data.size(); }
    bool empty() const { return data.empty(); }
};

void measureComplexity(int n) {
    vector<int> arr(n);
    mt19937 rng(123);
    generate(arr.begin(), arr.end(), rng);

    BinaryHeap h1, h2;

    auto t1 = high_resolution_clock::now();
    for (int x : arr) h1.insert(x);
    auto t2 = high_resolution_clock::now();

    auto t3 = high_resolution_clock::now();
    h2.build(arr);
    auto t4 = high_resolution_clock::now();

    double alg1 = duration<double, micro>(t2 - t1).count();
    double alg2 = duration<double, micro>(t4 - t3).count();

    cout << "  n =" << setw(8) << n
         << " | Alg1 (inserts): " << setw(10) << fixed << setprecision(2) << alg1 << " us"
         << " | Alg2 (build): "   << setw(10) << alg2 << " us\n";
}

void measurePQ(const string& label, vector<int> baseData) {
    const int OPS = 10000;
    vector<int> extra(OPS);
    mt19937 rng(42);
    generate(extra.begin(), extra.end(), rng);

    BinaryHeap h1;
    for (int x : baseData) h1.insert(x);
    auto t1 = high_resolution_clock::now();
    for (int x : extra) h1.insert(x);
    auto t2 = high_resolution_clock::now();
    double insTime = duration<double, micro>(t2 - t1).count();

    BinaryHeap h2;
    for (int x : baseData) h2.insert(x);
    for (int x : extra) h2.insert(x);
    auto t3 = high_resolution_clock::now();
    for (int i = 0; i < OPS && !h2.empty(); i++) h2.deleteMin();
    auto t4 = high_resolution_clock::now();
    double delTime = duration<double, micro>(t4 - t3).count();

    cout << "  " << label
         << " | Insert x" << OPS << ": " << fixed << setprecision(2) << insTime << " us"
         << " | DeleteMin x" << OPS << ": " << delTime << " us\n";
}

int main() {
    vector<int> input = {10, 12, 1, 14, 6, 5, 8, 15, 3, 9, 7, 4, 11, 13, 2};

    cout << "=== Task a: One-by-one insertion (Algorithm 1) ===\n";
    BinaryHeap heap1;
    for (int x : input) heap1.insert(x);
    cout << "Array: "; heap1.print();

    cout << "\n=== Task b: Linear-time build (Algorithm 2) ===\n";
    BinaryHeap heap2;
    heap2.build(input);
    cout << "Array: "; heap2.print();

    cout << "\n=== Task c: Traversals ===\n";
    cout << "Heap1 (Alg1):\n"; heap1.printTraversals();
    cout << "\nHeap2 (Alg2):\n"; heap2.printTraversals();

    cout << "\n=== Task d: Complexity (microseconds) ===\n";
    for (int n : {100, 1000, 10000, 100000, 1000000})
        measureComplexity(n);

    cout << "\n=== Task e: Priority Queue - Insert vs DeleteMin ===\n";
    measurePQ("Heap1 base (Alg1)", input);
    measurePQ("Heap2 base (Alg2)", input);

    return 0;
}
