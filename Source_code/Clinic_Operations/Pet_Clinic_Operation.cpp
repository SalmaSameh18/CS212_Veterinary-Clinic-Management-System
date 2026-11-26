#include <iostream>
#include <string>
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


void displayMenu()
{
    cout << "\n";
    cout << "====================================\n";
    cout << "       VETERINARY CLINIC SYSTEM     \n";
    cout << "====================================\n";

    cout << "1. Register New Pet\n";
    cout << "2. Search Pet By ID\n";
    cout << "3. Delete Pet\n";
    cout << "4. Display All Pets\n";
    cout << "5. Check In Pet\n";
    cout << "6. Complete Visit\n";
    cout << "7. Display Recent Visit History\n";
    cout << "8. Sort Pets By Name\n";
    cout << "0. Exit\n";

    cout << "====================================\n";
    cout << "Enter your choice: ";
}



int main()
{
    PetList petList;
    PetBST petTree;
    PetQueue waitingQueue;
    VisitStack visitHistory;

    ClinicOperations clinic(
        petList,
        petTree,
        waitingQueue,
        visitHistory
    );

    int choice;

    while (true)
    {
        displayMenu();

        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number.\n";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            continue;
        }

        switch (choice)
        {
        case 1:
            clinic.registerPetForVisit();
            break;

        case 2:
        {
            int id;

            cout << "Enter Pet ID: ";

            if (!(cin >> id))
            {
                cout << "Invalid ID.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            Pet* pet = petTree.search(id);

            if (pet != nullptr)
            {
                cout << "\nPet Found!\n";
                cout << "ID: " << pet->id << endl;
                cout << "Name: " << pet->name << endl;
                cout << "Species: " << pet->species << endl;
                cout << "Age: " << pet->age << endl;
                cout << "Owner: " << pet->owner << endl;
            }
            else
            {
                cout << "Pet not found.\n";
            }

            break;
        }

        case 3:
        {
            int id;

            cout << "Enter Pet ID: ";

            if (!(cin >> id))
            {
                cout << "Invalid ID.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            if (petTree.search(id) != nullptr)
            {
                petList.deletePet(id);
                petTree.deletePet(id);

                cout << "Pet deleted successfully.\n";
            }
            else
            {
                cout << "Pet not found.\n";
            }

            break;
        }

        case 4:
            petList.display();
            break;

        case 5:
            clinic.checkInPet();
            break;

        case 6:
            clinic.completeVisit();
            break;

        case 7:
            visitHistory.display();
            break;

        case 8:
            clinic.sortPetsByName();
            break;

        case 0:
            cout << "\nThank you for using the system!\n";
            return 0;

        default:
            cout << "Invalid choice. Please try again.\n";
        }

        cout << "\n";
    }

    return 0;
}
