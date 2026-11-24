#include <iostream>
#include <string>

using namespace std;

// Pet Structure
struct Pet
{
    int id;
    string name;
    string species;
    int age;
    string gender;
    string owner;
    string phone;
    string medicalNote;
};

class PetList
{
private:

    struct Node
    {
        Pet data;
        Node* next;

        Node(const Pet& p)
        {
            data = p;
            next = nullptr;
        }
    };

    Node* head;
    int count;

public:

    // Constructor
    PetList()
    {
        head = nullptr;
        count = 0;
    }

    // 1. Insert
    bool insert(Pet p)
    {
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
            Node* current = head;

            while (current->next != nullptr)
            {
                current = current->next;
            }

            current->next = newNode;
        }

        count++;
        return true;
    }

    // 2. Delete
    bool deletePet(int id)
    {
        Node* current = head;
        Node* previous = nullptr;

        while (current != nullptr && current->data.id != id)
        {
            previous = current;
            current = current->next;
        }

        if (current == nullptr)
        {
            return false;
        }

        if (previous == nullptr)
        {
            head = current->next;
        }
        else
        {
            previous->next = current->next;
        }

        delete current;
        count--;

        return true;
    }

    // 3. Search
    Pet* search(int id)
    {
        Node* current = head;

        while (current != nullptr)
        {
            if (current->data.id == id)
            {
                return &current->data;
            }

            current = current->next;
        }

        return nullptr;
    }

    // 4. Display
    void display() const
    {
        if (isEmpty())
        {
            cout << "No pet records found.\n";
            return;
        }

        const Node* current = head;

        while (current != nullptr)
        {
            cout << "ID: " << current->data.id << endl;
            cout << "Name: " << current->data.name << endl;
            cout << "Species: " << current->data.species << endl;
            cout << "Age: " << current->data.age << endl;
            cout << "Gender: " << current->data.gender << endl;
            cout << "Owner: " << current->data.owner << endl;
            cout << "Phone: " << current->data.phone << endl;
            cout << "Medical Note: " << current->data.medicalNote << endl;

            cout << "-------------------------\n";

            current = current->next;
        }
    }

    // 5. Is Empty
    bool isEmpty() const
    {
        return head == nullptr;
    }

    // 6. Size
    int size() const
    {
        return count;
    }

};
