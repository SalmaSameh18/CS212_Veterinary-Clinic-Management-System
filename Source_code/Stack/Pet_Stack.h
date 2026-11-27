#ifndef VISIT_STACK_H
#define VISIT_STACK_H

#include <string>

class VisitStack
{
private:
    static const int MAX_VISITS = 100;
    std::string items[MAX_VISITS];
    int topIndex;

public:
    VisitStack();

    bool isEmpty() const;
    bool isFull() const;
    int size() const;

    bool push(const std::string& visitor);
    bool pop(std::string& visitor);
    bool peek(std::string& visitor) const;

    void display() const;
    void clear();
};

#endif // VISIT_STACK_H
