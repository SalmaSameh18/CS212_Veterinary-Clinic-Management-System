#ifndef VISIT_STACK_H
#define VISIT_STACK_H

#include <string>
#include "Constants.h"

using namespace std;

class VisitStack {
private:
    string items[MAX_PETS];
    int topIndex;

public:
    VisitStack();

    bool isEmpty() const;
    bool isFull() const;
    int size() const;

    bool push(const string& visitor);
    bool pop(string& visitor);
    bool peek(string& visitor) const;

    void display() const;
    void clear();
};

#endif
