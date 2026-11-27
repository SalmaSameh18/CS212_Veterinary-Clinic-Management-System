#ifndef PET_LIST_H
#define PET_LIST_H

#include "../Main/Pet.h"

using namespace std;

class PetList
{
private:
    static const int MAX_LIST_SIZE = 100;

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

    // Copies current records into a caller-provided array (for sorting/searching)
    int copyToArray(Pet arr[], int capacity) const;

    bool insert(const Pet& p);
    bool deletePet(int id);
    bool updatePet(int id, const Pet& updatedPet);
    Pet* search(int id);

    void display() const;

    bool isEmpty() const;
    int size() const;
};

#endif // PET_LIST_H
