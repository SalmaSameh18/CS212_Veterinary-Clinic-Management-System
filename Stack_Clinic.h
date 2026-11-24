
#ifndef VISITSTACK_H
#define VISITSTACK_H

#include <iostream>
#include <string>
using namespace std;

const int MAX_PETS = 100;

class VisitStack {
private:
    string items[MAX_PETS];
    int topIndex;

public:
    VisitStack() : topIndex(-1) {}

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex == MAX_PETS - 1;
    }

    int size() const {
        return topIndex + 1;
    }

    bool push(const string& visitor) {
        if (isFull()) {
            cout << "Stack is full. Cannot push " << visitor << endl;
            return false;
        }

        items[++topIndex] = visitor;
        return true;
    }

    bool pop(string& visitor) {
        if (isEmpty()) {
            cout << "Stack is empty. Cannot pop." << endl;
            return false;
        }

        visitor = items[topIndex--];
        return true;
    }

    bool peek(string& visitor) const {
        if (isEmpty()) {
            cout << "Stack is empty. Cannot peek." << endl;
            return false;
        }

        visitor = items[topIndex];
        return true;
    }

    void display() const {
        if (isEmpty()) {
            cout << "No completed visits yet.\n";
            return;
        }

        cout << "Recent visits (newest first):\n";

        for (int i = topIndex; i >= 0; --i) {
            cout << " - " << items[i] << "\n";
        }
    }

    void clear() {
        topIndex = -1;
    }
};

#endif
