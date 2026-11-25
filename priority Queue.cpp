#include <iostream>
using namespace std;
const int MAX_ITEMS = 100;

class PetQueue {

private:

    struct Pet {
        int id;
        int priority;
    };

    Pet items[MAX_ITEMS];
    int count;

public:

    // Constructor
    PetQueue() : count(0) {}

    // Check if queue is empty
    bool isEmpty() const {
        return count == 0;
    }

    // Check if queue is full
    bool isFull() const {
        return count == MAX_ITEMS;
    }

    // Return number of pets
    int size() const {
        return count;
    }

    // Add pet according to priority
    bool enqueue(int id, int priority = 0) {

        if (isFull())
            return false;

        int i = count - 1;

        while (i >= 0 && items[i].priority < priority) {
            items[i + 1] = items[i];
            --i;
        }

        items[i + 1].id = id;
        items[i + 1].priority = priority;

        ++count;

        return true;
    }

    // Remove pet from front
    bool dequeue(int& id) {

        if (isEmpty())
            return false;

        id = items[0].id;

        for (int i = 0; i < count - 1; ++i) {
            items[i] = items[i + 1];
        }

        --count;

        return true;
    }

    // Get front pet
    bool front(int& id) const {

        if (isEmpty())
            return false;

        id = items[0].id;

        return true;
    }

    // Get rear pet
    bool rear(int& id) const {

        if (isEmpty())
            return false;

        id = items[count - 1].id;

        return true;
    }

    // Search for a pet by ID
    bool contains(int id) const {

        for (int i = 0; i < count; ++i) {

            if (items[i].id == id)
                return true;
        }

        return false;
    }

    // Remove pet by ID
    bool removeById(int id) {

        for (int i = 0; i < count; ++i) {

            if (items[i].id == id) {

                for (int j = i; j < count - 1; ++j) {
                    items[j] = items[j + 1];
                }

                --count;

                return true;
            }
        }

        return false;
    }

    // Display all pets
    void display() const {

        if (isEmpty()) {
            cout << "Waiting queue is empty.\n";
            return;
        }

        cout << "Waiting pets (Highest to Lowest Priority):\n";

        for (int i = 0; i < count; ++i) {

            cout << " - Pet ID: " << items[i].id
                 << " | Priority: " << items[i].priority
                 << '\n';
        }
    }

}; // End of class


int main() {

    return 0;
}
