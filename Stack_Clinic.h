#ifndef VISIT_STACK_H
#define VISIT_STACK_H
#include <string>
using namespace std;

class VisitStack {
private:
    string items[MAX_PETS];
    int topIndex;

public:

    // Constructor
    VisitStack();

    // Check if stack is empty
    bool isEmpty() const;

    // Check if stack is full
    bool isFull() const;

    // Return number of elements
    int size() const;

    // Push a new visitor
    bool push(const string& visitor);

    // Pop the top visitor
    bool pop(string& visitor);

    // Return the top visitor without removing it
    bool peek(string& visitor) const;

    // Display all visitors
    void display() const;

    // Clear the stack
    void clear();
};

#endif
