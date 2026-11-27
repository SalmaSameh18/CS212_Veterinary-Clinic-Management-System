#include "Pet_Stack.h"
#include <iostream>

using namespace std;

VisitStack::VisitStack()
{
    topIndex = -1;
}

bool VisitStack::isEmpty() const
{
    return topIndex == -1;
}

bool VisitStack::isFull() const
{
    return topIndex >= MAX_VISITS - 1;
}

int VisitStack::size() const
{
    return topIndex + 1;
}

bool VisitStack::push(const string& visitor)
{
    if (isFull())
    {
        return false;
    }
    topIndex++;
    items[topIndex] = visitor;
    return true;
}

bool VisitStack::pop(string& visitor)
{
    if (isEmpty())
    {
        return false;
    }
    visitor = items[topIndex];
    topIndex--;
    return true;
}

bool VisitStack::peek(string& visitor) const
{
    if (isEmpty())
    {
        return false;
    }
    visitor = items[topIndex];
    return true;
}

void VisitStack::display() const
{
    if (isEmpty())
    {
        cout << "Visit history stack is empty.\n";
        return;
    }

    cout << "Visit History (Most Recent First):\n";
    for (int i = topIndex; i >= 0; i--)
    {
        cout << "  - " << items[i] << "\n";
    }
}

void VisitStack::clear()
{
    topIndex = -1;
}