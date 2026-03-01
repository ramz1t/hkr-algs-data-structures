#include <iostream>
#include <stdexcept>
#include <string>

struct Contact {
    std::string name;
    std::string address;
    Contact* next = nullptr;

    Contact(const std::string& n, const std::string& a) : name(n), address(a), next(nullptr) {}
};

class AddressBook {
public:
    AddressBook() : head(nullptr), count(0) {}

    ~AddressBook() {
        Contact* current = head;
        while (current) {
            Contact* next = current->next;
            delete current;
            current = next;
        }
    }

    void add(const std::string& name, const std::string& address) {
        Contact* node = new Contact(name, address);
        if (!head) {
            head = node;
        } else {
            Contact* tail = head;
            while (tail->next) tail = tail->next;
            tail->next = node;
        }
        ++count;
        std::cout << "[AddressBook] Added contact #" << (count - 1)
                  << ": " << name << "\n";
    }

    void remove(int index) {
        checkIndex(index);
        Contact* toDelete = nullptr;
        if (index == 0) {
            toDelete = head;
            head = head->next;
        } else {
            Contact* prev = nodeAt(index - 1);
            toDelete = prev->next;
            prev->next = toDelete->next;
        }
        std::cout << "[AddressBook] Removed contact: " << toDelete->name << "\n";
        delete toDelete;
        --count;
    }

    const Contact& get(int index) const {
        checkIndex(index);
        return *nodeAt(index);
    }

    void print() const {
        if (!head) {
            std::cout << "(address book is empty)\n";
            return;
        }
        std::cout << "\n--- Address Book (" << count << " contact"
                  << (count == 1 ? "" : "s") << ") ---\n";
        int idx = 0;
        for (const Contact* c = head; c; c = c->next, ++idx) {
            std::cout << "  [" << idx << "] " << c->name
                      << " | " << c->address << "\n";
        }
        std::cout << "-------------------------------\n";
    }

    int size() const { return count; }

private:
    Contact* head;
    int      count;

    Contact* nodeAt(int index) const {
        Contact* current = head;
        for (int i = 0; i < index; ++i) current = current->next;
        return current;
    }

    void checkIndex(int index) const {
        if (index < 0 || index >= count) {
            throw std::out_of_range(
                "AddressBook: index " + std::to_string(index) +
                " out of range (size=" + std::to_string(count) + ")");
        }
    }
};

int main() {
    AddressBook book;

    book.add("Alice Andersson",   "Storgatan 1, 211 11 Malmö");
    book.add("Bob Bergström",     "Kungsgatan 5, 111 43 Stockholm");
    book.add("Clara Carlsson",    "Avenyn 12, 411 36 Göteborg");
    book.add("David Davidsson",   "Lilla Torg 3, 211 34 Malmö");
    book.add("Eva Eriksson",      "Strandvägen 8, 114 56 Stockholm");

    book.print();

    std::cout << "\nget(2): " << book.get(2).name
              << " | " << book.get(2).address << "\n";

    book.remove(1);
    book.remove(0);

    book.print();

    std::cout << "\nTrying get(99):\n";
    try {
        book.get(99);
    } catch (const std::out_of_range& e) {
        std::cerr << "  Exception: " << e.what() << "\n";
    }

    AddressBook single;
    single.add("Only Person", "Lonesome Road 1");
    single.remove(0);
    single.print();

    return 0;
}
