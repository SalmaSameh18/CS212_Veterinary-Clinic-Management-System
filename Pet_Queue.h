#ifndef PET_QUEUE_H
#define PET_QUEUE_H

using namespace std;

class PetQueue
{
private:
    static const int MAX_QUEUE_SIZE = 100;

    struct QueueItem
    {
        int id;
        int priority;
    };

    QueueItem items[MAX_QUEUE_SIZE];
    int count;

public:
    PetQueue();

    bool isEmpty() const;
    bool isFull() const;
    int size() const;

    bool enqueue(int id, int priority = 0);
    bool dequeue(int& id);
    bool front(int& id) const;
    bool rear(int& id) const;

    bool contains(int id) const;
    bool removeById(int id);

    void display() const;
};

#endif // PET_QUEUE_H