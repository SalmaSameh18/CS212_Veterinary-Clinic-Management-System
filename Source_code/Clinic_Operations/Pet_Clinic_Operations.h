#ifndef CLINICOPERATIONS_H
#define CLINICOPERATIONS_H

#include <iostream>
#include <string>
#include <limits>

using namespace std;

const int MAX_PETS = 100;

class ClinicOperations
{
private:

    PetList& petList;
    PetBST& petTree;
    PetQueue& waitingQueue;
    VisitStack& visitHistory;

public:

    // Constructor
    ClinicOperations(PetList& list, PetBST& tree,
        PetQueue& queue, VisitStack& history)
        : petList(list),
        petTree(tree),
        waitingQueue(queue),
        visitHistory(history)
    {
    }

    // 1. Validate Pet ID
    bool validatePetID(int id)
    {
        if (id <= 0)
        {
            cout << "Invalid ID. ID must be positive.\n";
            return false;
        }

        if (petList.search(id) != nullptr ||
            petTree.search(id) != nullptr)
        {
            cout << "Pet ID already exists.\n";
            return false;
        }

        return true;
    }

    // 2. Validate Pet Input
    bool validatePetInput(const Pet& p)
    {
        if (p.name.empty())
        {
            cout << "Pet name cannot be empty.\n";
            return false;
        }

        if (p.species.empty())
        {
            cout << "Pet species cannot be empty.\n";
            return false;
        }

        if (p.age < 0)
        {
            cout << "Invalid age.\n";
            return false;
        }

        if (p.owner.empty())
        {
            cout << "Owner name cannot be empty.\n";
            return false;
        }

        return true;
    }

    // 3. Register Pet For Visit
    bool registerPetForVisit()
    {
        Pet p;

        cout << "\nEnter Pet ID: ";

        if (!(cin >> p.id))
        {
            cout << "Invalid ID input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!validatePetID(p.id))
        {
            return false;
        }

        cout << "Enter Pet Name: ";
        getline(cin, p.name);

        cout << "Enter Species: ";
        getline(cin, p.species);

        cout << "Enter Age: ";

        if (!(cin >> p.age))
        {
            cout << "Invalid age input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Owner Name: ";
        getline(cin, p.owner);

        cout << "Enter Phone: ";
        getline(cin, p.phone);

        cout << "Enter Gender: ";
        getline(cin, p.gender);

        cout << "Enter Medical Note: ";
        getline(cin, p.medicalNote);

        if (!validatePetInput(p))
        {
            return false;
        }

        if (!petList.insert(p))
        {
            cout << "Failed to register pet in Linked List.\n";
            return false;
        }

        if (!petTree.insert(p))
        {
            petList.deletePet(p.id);

            cout << "Failed to register pet in BST.\n";
            return false;
        }

        cout << "\nPet registered successfully!\n";

        return true;
    }

    // 4. Check In Pet
    bool checkInPet()
    {
        int id;

        cout << "\nEnter Pet ID: ";

        if (!(cin >> id))
        {
            cout << "Invalid ID input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }

        if (id <= 0)
        {
            cout << "Invalid Pet ID.\n";
            return false;
        }

        Pet* pet = petTree.search(id);

        if (pet == nullptr || petList.search(id) == nullptr)
        {
            cout << "Pet not found.\n";
            return false;
        }

        if (waitingQueue.contains(id))
        {
            cout << "Pet is already in the waiting queue.\n";
            return false;
        }

        if (!waitingQueue.enqueue(id))
        {
            cout << "Waiting queue is full.\n";
            return false;
        }

        cout << "Pet checked in successfully!\n";

        return true;
    }

    // 5. Complete Visit
    bool completeVisit()
    {
        int id;

        if (waitingQueue.isEmpty())
        {
            cout << "No pets waiting for a visit.\n";
            return false;
        }

        if (visitHistory.isFull())
        {
            cout << "Visit history stack is full.\n";
            return false;
        }

        if (!waitingQueue.front(id))
        {
            return false;
        }

        Pet* pet = petTree.search(id);

        if (pet == nullptr)
        {
            cout << "Pet record not found.\n";
            return false;
        }

        string visitRecord =
            "ID: " + to_string(pet->id) +
            " | Name: " + pet->name;

        int removedID;

        if (!waitingQueue.dequeue(removedID))
        {
            cout << "Failed to remove pet from queue.\n";
            return false;
        }

        if (!visitHistory.push(visitRecord))
        {
            cout << "Failed to save visit history.\n";
            return false;
        }

        cout << "\nVisit completed successfully!\n";
        cout << "Pet Name: " << pet->name << endl;
        cout << "Pet ID: " << id << endl;

        return true;
    }

    // 6. Sort Pets By Name
    void sortPetsByName()
    {
        Pet pets[MAX_PETS];

        int count = petList.copyToArray(pets, MAX_PETS);

        if (count == 0)
        {
            cout << "No pet records found.\n";
            return;
        }

        // Bubble Sort
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count - i - 1; j++)
            {
                if (pets[j].name > pets[j + 1].name)
                {
                    Pet temp = pets[j];
                    pets[j] = pets[j + 1];
                    pets[j + 1] = temp;
                }
            }
        }

        cout << "\nPets Sorted By Name:\n";

        for (int i = 0; i < count; i++)
        {
            cout << "ID: " << pets[i].id
                << " | Name: " << pets[i].name << endl;
        }
    }

};

#endif // CLINICOPERATIONS_H
