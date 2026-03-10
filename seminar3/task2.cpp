#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <iomanip>

using namespace std;

const vector<int> INPUT = {4371, 1323, 6173, 4199, 4344, 9679, 1989};
const int TABLE_SIZE = 10;

int h(int x, int size = TABLE_SIZE) { return x % size; }

void separateChaining() {
    vector<list<int>> table(TABLE_SIZE);
    for (int x : INPUT)
        table[h(x)].push_back(x);

    cout << "=== a) Separate Chaining ===\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "[" << i << "]: ";
        for (int v : table[i]) cout << v << " -> ";
        cout << "NULL\n";
    }
}

void linearProbing() {
    vector<int> table(TABLE_SIZE, -1);
    cout << "\n=== b) Linear Probing ===\n";
    for (int x : INPUT) {
        int pos = h(x), probes = 0;
        while (table[(pos + probes) % TABLE_SIZE] != -1) probes++;
        int dest = (pos + probes) % TABLE_SIZE;
        table[dest] = x;
        cout << "Insert " << x << ": h=" << pos << " -> placed at [" << dest << "]";
        if (probes) cout << "  (probes=" << probes << ")";
        cout << "\n";
    }
    cout << "Table: ";
    for (int i = 0; i < TABLE_SIZE; i++)
        cout << "[" << i << "]=" << (table[i] == -1 ? "_" : to_string(table[i])) << " ";
    cout << "\n";
}

void quadraticProbing() {
    vector<int> table(TABLE_SIZE, -1);
    cout << "\n=== c) Quadratic Probing ===\n";
    for (int x : INPUT) {
        int pos = h(x), i = 0;
        while (table[(pos + i * i) % TABLE_SIZE] != -1) i++;
        int dest = (pos + i * i) % TABLE_SIZE;
        table[dest] = x;
        cout << "Insert " << x << ": h=" << pos << " -> placed at [" << dest << "]";
        if (i) cout << "  (i=" << i << ")";
        cout << "\n";
    }
    cout << "Table: ";
    for (int i = 0; i < TABLE_SIZE; i++)
        cout << "[" << i << "]=" << (table[i] == -1 ? "_" : to_string(table[i])) << " ";
    cout << "\n";
}

void complexity() {
    cout << "\n=== d) Complexity (alpha = load factor = n/m) ===\n";
    cout << "Separate chaining:\n";
    cout << "  Insert: O(1) average, O(n) worst (all keys map to same slot)\n";
    cout << "  Search: O(1 + alpha) average\n";
    cout << "Linear probing:\n";
    cout << "  Insert/Search: O(1/(1-alpha)) average\n";
    cout << "  Primary clustering: long consecutive runs degrade performance\n";
    cout << "Quadratic probing:\n";
    cout << "  Eliminates primary clustering; secondary clustering possible\n";
    cout << "  Insert/Search: O(1/(1-alpha)) average (better constant)\n";
    cout << "  Requires prime table size and alpha < 0.5 to guarantee insertion\n";
}

int nextPrime(int n) {
    int limit = max(n * 2, 10);
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= limit; i++)
        if (isPrime[i])
            for (int j = i * i; j <= limit; j += i)
                isPrime[j] = false;
    for (int i = n; i <= limit; i++)
        if (isPrime[i]) return i;
    return n;
}

void rehash() {
    vector<int> old(TABLE_SIZE, -1);
    for (int x : INPUT) {
        int pos = h(x), i = 0;
        while (old[(pos + i) % TABLE_SIZE] != -1) i++;
        old[(pos + i) % TABLE_SIZE] = x;
    }

    int newSize = nextPrime(TABLE_SIZE * 2);
    vector<int> table(newSize, -1);

    cout << "\n=== e) Rehash: size " << TABLE_SIZE << " -> " << newSize
         << "  (h(x) = x mod " << newSize << ") ===\n";
    cout << "Old table: ";
    for (int i = 0; i < TABLE_SIZE; i++)
        cout << "[" << i << "]=" << (old[i] == -1 ? "_" : to_string(old[i])) << " ";
    cout << "\n";

    for (int x : old) {
        if (x == -1) continue;
        int pos = x % newSize, i = 0;
        while (table[(pos + i) % newSize] != -1) i++;
        table[(pos + i) % newSize] = x;
    }

    cout << "New table: ";
    for (int i = 0; i < newSize; i++)
        cout << "[" << i << "]=" << (table[i] == -1 ? "_" : to_string(table[i])) << " ";
    cout << "\n";
}

void otherRehashing() {
    cout << "\n=== f) Other Rehashing Functions ===\n";
    cout << "1. Double hashing:      h(x,i) = (h1(x) + i*h2(x)) mod m\n";
    cout << "   h2(x) = R - (x mod R), R prime < m => spreads keys uniformly\n";
    cout << "2. Multiplication:      h(x) = floor(m * frac(x * A)), A~0.618\n";
    cout << "   Less sensitive to table size; good for power-of-2 sizes\n";
    cout << "3. Universal hashing:   h(x) = ((a*x + b) mod p) mod m\n";
    cout << "   p prime > key universe, random a,b => O(1) expected worst case\n";
    cout << "4. Robin Hood hashing:  displace keys with shorter probe distance\n";
    cout << "   Reduces variance in probe lengths; cache-friendly open addressing\n";
}

int main() {
    separateChaining();
    linearProbing();
    quadraticProbing();
    complexity();
    rehash();
    otherRehashing();
    return 0;
}
