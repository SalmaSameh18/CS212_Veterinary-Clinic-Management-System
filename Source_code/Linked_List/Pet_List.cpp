#include <iostream>
#include <string>
using namespace std;
const int MAX_PETS = 100;

struct Pet {
    int id;
    string name;
    string species;
    int age;
    string owner;
    string phone;
    string gender;
    string medicalNote;
};

// LINKED LIST

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

    PetList()
    {
        head = nullptr;
        count = 0;
    }

 ~PetList()
    {
        Node* current = head;

        while (current != nullptr)
        {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

int copyToArray(Pet arr[], int capacity) const
{
    int i = 0;
    Node* current = head;

    while (current != nullptr && i < capacity)
    {
        arr[i] = current->data;
        current = current->next;
        i++;
    }

    return i;
}

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

    bool isEmpty() const
    {
        return head == nullptr;
    }

    int size() const
    {
        return count;
    }
};

int main(){
    return 0;
}
