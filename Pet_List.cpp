#include "Pet_List.h"
#include <iostream>

using namespace std;

PetList::Node::Node(const Pet& p)
{
    data = p;
    next = nullptr;
}

PetList::PetList()
{
    head = nullptr;
    count = 0;
}

PetList::~PetList()
{
    Node* curr = head;
    while (curr != nullptr)
    {
        Node* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    head = nullptr;
    count = 0;
}

int PetList::copyToArray(Pet arr[], int capacity) const
{
    int copied = 0;
    Node* curr = head;
    while (curr != nullptr && copied < capacity)
    {
        arr[copied] = curr->data;
        copied++;
        curr = curr->next;
    }
    return copied;
}

bool PetList::insert(const Pet& p)
{
    if (count >= MAX_LIST_SIZE)
    {
        return false;
    }
    if (search(p.id) != nullptr)
    {
        return false;
    }

    Node* newNode = new Node(p);
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node* temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    count++;
    return true;
}

bool PetList::deletePet(int id)
{
    if (head == nullptr)
    {
        return false;
    }

    Node* curr = head;
    Node* prev = nullptr;

    while (curr != nullptr && curr->data.id != id)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr)
    {
        return false;
    }

    if (prev == nullptr)
    {
        head = curr->next;
    }
    else
    {
        prev->next = curr->next;
    }

    delete curr;
    count--;
    return true;
}

bool PetList::updatePet(int id, const Pet& updatedPet)
{
    Pet* target = search(id);
    if (target == nullptr)
    {
        return false;
    }

    Pet temp = updatedPet;
    temp.id = id;
    *target = temp;
    return true;
}

Pet* PetList::search(int id)
{
    Node* curr = head;
    while (curr != nullptr)
    {
        if (curr->data.id == id)
        {
            return &(curr->data);
        }
        curr = curr->next;
    }
    return nullptr;
}

void PetList::display() const
{
    if (isEmpty())
    {
        cout << "No pet records in the linked list.\n";
        return;
    }

    Node* curr = head;
    int idx = 1;
    while (curr != nullptr)
    {
        cout << idx++ << ". [ID: " << curr->data.id << "] "
             << curr->data.name << " | Species: " << curr->data.species
             << " | Age: " << curr->data.age << " | Gender: " << curr->data.gender << "\n"
             << "   Owner: " << curr->data.owner << " (" << curr->data.phone << ")\n"
             << "   Note: " << curr->data.medicalNote << "\n";
        curr = curr->next;
    }
}

bool PetList::isEmpty() const
{
    return head == nullptr;
}

int PetList::size() const
{
    return count;
}