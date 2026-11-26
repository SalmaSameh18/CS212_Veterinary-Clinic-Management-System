#ifndef PETQUEUE_H
#define PETQUEUE_H

const int MAX_PETS = 100;

class PetQueue {

private:

    struct Pet {
        int id;
        int priority;
    };

    Pet items[MAX_PETS];
    int count;

public:

    // Constructor
    PetQueue();

    // Check if queue is empty
    bool isEmpty() const;

    // Check if queue is full
    bool isFull() const;

    // Return number of pets
    int size() const;

    // Add pet according to priority
    bool enqueue(int id, int priority = 0);

    // Remove pet from front
    bool dequeue(int& id);

    // Get front pet
    bool front(int& id) const;

    // Get rear pet
    bool rear(int& id) const;

    // Search for a pet by ID
    bool contains(int id) const;

    // Remove pet by ID
    bool removeById(int id);

    // Display all pets
    void display() const;

}; // End of class

#endif
