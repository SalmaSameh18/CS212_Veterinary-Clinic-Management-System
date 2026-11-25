#ifndef PETQUEUE_H
#define PETQUEUE_H

const int MAX_PETS = 100;

class PetQueue {
private:
    int ids[MAX_PETS];
    int frontposition, rearposition, count;

public:
    PetQueue();

    bool isEmpty() const;
    bool isFull() const;
    int size() const;

    bool enqueue(int id);
    bool dequeue(int& id);

    bool front(int& id) const;
    bool rear(int& id) const;

    bool contains(int id) const;
    bool removeById(int id);

    void display() const;
};

#endif
