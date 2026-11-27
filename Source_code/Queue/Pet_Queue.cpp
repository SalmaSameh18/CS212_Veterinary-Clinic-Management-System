#include "PetQueue.h"
#include <iostream>

using namespace std;

PetQueue::PetQueue()
{
    count = 0;
}

bool PetQueue::isEmpty() const
{
    return count == 0;
}

bool PetQueue::isFull() const
{
    return count >= MAX_QUEUE_SIZE;
}

int PetQueue::size() const
{
    return count;
}

// Higher priority value comes closer to the front (index 0); ties stay FIFO
bool PetQueue::enqueue(int id, int priority)
{
    if (isFull())
    {
        return false;
    }

    int pos = count;
    while (pos > 0 && items[pos - 1].priority < priority)
    {
        items[pos] = items[pos - 1];
        pos--;
    }

    items[pos].id = id;
    items[pos].priority = priority;
    count++;
    return true;
}

bool PetQueue::dequeue(int& id)
{
    if (isEmpty())
    {
        return false;
    }

    id = items[0].id;
    for (int i = 0; i < count - 1; i++)
    {
        items[i] = items[i + 1];
    }
    count--;
    return true;
}

bool PetQueue::front(int& id) const
{
    if (isEmpty())
    {
        return false;
    }
    id = items[0].id;
    return true;
}

bool PetQueue::rear(int& id) const
{
    if (isEmpty())
    {
        return false;
    }
    id = items[count - 1].id;
    return true;
}

bool PetQueue::contains(int id) const
{
    for (int i = 0; i < count; i++)
    {
        if (items[i].id == id)
        {
            return true;
        }
    }
    return false;
}

bool PetQueue::removeById(int id)
{
    int foundIdx = -1;
    for (int i = 0; i < count; i++)
    {
        if (items[i].id == id)
        {
            foundIdx = i;
            break;
        }
    }

    if (foundIdx == -1)
    {
        return false;
    }

    for (int i = foundIdx; i < count - 1; i++)
    {
        items[i] = items[i + 1];
    }
    count--;
    return true;
}

void PetQueue::display() const
{
    if (isEmpty())
    {
        cout << "Waiting queue is empty.\n";
        return;
    }

    cout << "Waiting Queue (Front -> Rear): ";
    for (int i = 0; i < count; i++)
    {
        cout << "[ID: " << items[i].id << ", P:" << items[i].priority << "]";
        if (i < count - 1)
        {
            cout << " -> ";
        }
    }
    cout << "\n";
}
