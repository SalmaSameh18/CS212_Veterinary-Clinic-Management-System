#ifndef PETLIST_H
#define PETLIST_H

#include "Pet.h"

class PetList
{
private:
    struct Node
    {
        Pet data;
        Node* next;

        Node(const Pet& p);
    };

    Node* head;
    int count;

public:
    PetList();
    ~PetList();
    bool insert(Pet p);
    bool deletePet(int id);
    Pet* search(int id);
    void display() const;
    bool isEmpty() const;
    int size() const;
};

#endif
