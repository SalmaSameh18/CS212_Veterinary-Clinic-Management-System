#ifndef PET_STACK_H
#define PET_STACK_H

#include <string>

using namespace std;

class VisitStack
{
private:
    static const int MAX_VISITS = 100;
    string items[MAX_VISITS];
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

#endif // PET_STACK_H