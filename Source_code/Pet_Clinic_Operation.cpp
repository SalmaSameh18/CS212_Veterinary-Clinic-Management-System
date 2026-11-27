#include "Pet_Clinic_Operations.h"
#include <iostream>
#include <limits>

using namespace std;

ClinicOperations::ClinicOperations(PetList& list, PetBST& tree,
                                   PetQueue& queue, VisitStack& history)
    : petList(list), petTree(tree), waitingQueue(queue), visitHistory(history)
{
}

int ClinicOperations::readInt(const string& prompt) const
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Please enter a valid integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string ClinicOperations::readLine(const string& prompt) const
{
    string line;
    cout << prompt;
    getline(cin, line);
    return line;
}

bool ClinicOperations::validatePetID(int id) const
{
    return id > 0;
}

bool ClinicOperations::validatePetInput(const Pet& p) const
{
    if (!validatePetID(p.id))
    {
        cout << "Error: Pet ID must be a positive number.\n";
        return false;
    }
    if (p.name.empty() || p.species.empty() || p.owner.empty())
    {
        cout << "Error: Pet name, species, and owner name cannot be empty.\n";
        return false;
    }
    if (p.age < 0)
    {
        cout << "Error: Pet age cannot be negative.\n";
        return false;
    }
    return true;
}

bool ClinicOperations::registerPetForVisit()
{
    int id = readInt("Enter Pet ID: ");
    if (!validatePetID(id))
    {
        cout << "Error: ID must be greater than 0.\n";
        return false;
    }

    if (petTree.search(id) != nullptr || petList.search(id) != nullptr)
    {
        cout << "Error: A pet with ID " << id << " already exists.\n";
        return false;
    }

    Pet p;
    p.id = id;
    p.name = readLine("Enter Pet Name: ");
    p.species = readLine("Enter Species (e.g., Cat, Dog): ");
    p.age = readInt("Enter Age (years): ");
    p.gender = readLine("Enter Gender: ");
    p.owner = readLine("Enter Owner Name: ");
    p.phone = readLine("Enter Owner Phone: ");
    p.medicalNote = readLine("Enter Initial Medical Note: ");

    if (!validatePetInput(p))
    {
        return false;
    }

    if (!petList.insert(p))
    {
        cout << "Error: Could not insert into linked list (may be full).\n";
        return false;
    }

    Pet* storedPet = petList.search(id);
    if (storedPet != nullptr)
    {
        petTree.insert(*storedPet);
    }

    cout << "Pet \"" << p.name << "\" (ID: " << p.id << ") registered successfully.\n";
    return true;
}

bool ClinicOperations::updatePetRecord()
{
    int id = readInt("Enter Pet ID to update: ");
    if (!validatePetID(id))
    {
        cout << "Error: ID must be greater than 0.\n";
        return false;
    }

    Pet* existing = petTree.search(id);
    if (existing == nullptr)
    {
        cout << "Error: Pet with ID " << id << " was not found.\n";
        return false;
    }

    Pet updated;
    updated.id = id;
    updated.name = readLine("Enter New Pet Name: ");
    updated.species = readLine("Enter New Species: ");
    updated.age = readInt("Enter New Age (years): ");
    updated.gender = readLine("Enter New Gender: ");
    updated.owner = readLine("Enter New Owner Name: ");
    updated.phone = readLine("Enter New Owner Phone: ");
    updated.medicalNote = readLine("Enter New Medical Note: ");

    if (!validatePetInput(updated))
    {
        return false;
    }

    bool listUpdated = petList.updatePet(id, updated);
    bool treeUpdated = petTree.updatePet(id, updated);

    if (listUpdated && treeUpdated)
    {
        cout << "Pet ID " << id << " updated in both Linked List and BST.\n";
        return true;
    }

    cout << "Warning: Partial or failed update across data structures.\n";
    return false;
}

bool ClinicOperations::deletePetRecord()
{
    int id = readInt("Enter Pet ID to delete: ");
    if (!validatePetID(id))
    {
        cout << "Error: ID must be greater than 0.\n";
        return false;
    }

    if (petTree.search(id) == nullptr && petList.search(id) == nullptr)
    {
        cout << "Error: Pet with ID " << id << " was not found.\n";
        return false;
    }

    bool removedFromQueue = waitingQueue.removeById(id);
    bool removedFromTree = petTree.deletePet(id);
    bool removedFromList = petList.deletePet(id);

    if (removedFromList || removedFromTree)
    {
        cout << "Pet ID " << id << " deleted from records";
        if (removedFromQueue)
        {
            cout << " and removed from waiting queue";
        }
        cout << ".\n";
        return true;
    }

    cout << "Error: Could not delete Pet ID " << id << ".\n";
    return false;
}

bool ClinicOperations::checkInPet()
{
    int id = readInt("Enter registered Pet ID to check into waiting queue: ");
    Pet* pet = petTree.search(id);
    if (pet == nullptr)
    {
        cout << "Error: Pet ID " << id << " not found. Register the pet first.\n";
        return false;
    }

    if (waitingQueue.contains(id))
    {
        cout << "Notice: Pet ID " << id << " is already in the waiting queue.\n";
        return false;
    }

    int priority = readInt("Enter priority level (0 = normal, 1 = urgent, 2 = emergency): ");
    if (!waitingQueue.enqueue(id, priority))
    {
        cout << "Error: Waiting queue is full.\n";
        return false;
    }

    cout << "Checked in " << pet->name << " (ID: " << id << ") with priority " << priority << ".\n";
    return true;
}

bool ClinicOperations::completeVisit()
{
    int nextId;
    if (!waitingQueue.dequeue(nextId))
    {
        cout << "No pets currently waiting in the queue.\n";
        return false;
    }

    Pet* pet = petTree.search(nextId);
    if (pet == nullptr)
    {
        cout << "Warning: Dequeued Pet ID " << nextId << " was not found in records.\n";
        return false;
    }

    cout << "Treating Pet: " << pet->name << " (ID: " << pet->id << ", Owner: " << pet->owner << ")\n";
    string newNote = readLine("Enter visit treatment note: ");
    pet->medicalNote = newNote;
    petList.updatePet(nextId, *pet);
    petTree.updatePet(nextId, *pet);

    string logEntry = "Pet #" + to_string(pet->id) + " (" + pet->name + ") - " + newNote;
    visitHistory.push(logEntry);

    cout << "Visit completed, medical note updated, and visit logged to stack.\n";
    return true;
}

bool ClinicOperations::undoLastVisit()
{
    string lastVisit;
    if (!visitHistory.pop(lastVisit))
    {
        cout << "Visit history stack is empty. Nothing to undo/pop.\n";
        return false;
    }
    cout << "Popped latest visit log: " << lastVisit << "\n";
    return true;
}

void ClinicOperations::searchPetById() const
{
    int id = readInt("Enter Pet ID to search (BST): ");
    Pet* found = petTree.search(id);
    if (found == nullptr)
    {
        cout << "No pet found with ID " << id << ".\n";
        return;
    }

    cout << "Found -> ID: " << found->id
         << " | Name: " << found->name
         << " | Species: " << found->species
         << " | Age: " << found->age
         << " | Owner: " << found->owner
         << " | Note: " << found->medicalNote << "\n";
}

void ClinicOperations::searchPetByName() const
{
    string target = readLine("Enter Pet Name to search (Linear Search): ");
    Pet tempArr[MAX_CLINIC_PETS];
    int n = petList.copyToArray(tempArr, MAX_CLINIC_PETS);

    int matches = 0;
    for (int i = 0; i < n; i++)
    {
        if (tempArr[i].name == target)
        {
            cout << "Match -> ID: " << tempArr[i].id
                 << " | Name: " << tempArr[i].name
                 << " | Age: " << tempArr[i].age
                 << " | Owner: " << tempArr[i].owner << "\n";
            matches++;
        }
    }

    if (matches == 0)
    {
        cout << "No pet found with name \"" << target << "\".\n";
    }
}

void ClinicOperations::sortPetsByName() const
{
    Pet arr[MAX_CLINIC_PETS];
    int n = petList.copyToArray(arr, MAX_CLINIC_PETS);
    if (n == 0)
    {
        cout << "No records to sort.\n";
        return;
    }

    for (int i = 1; i < n; i++)
    {
        Pet key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].name > key.name)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }

    cout << "Pets Sorted by Name (Insertion Sort):\n";
    for (int i = 0; i < n; i++)
    {
        cout << (i + 1) << ". " << arr[i].name << " (ID: " << arr[i].id
             << ", Age: " << arr[i].age << ")\n";
    }
}

void ClinicOperations::displaySystemOverview() const
{
    cout << "\n--- Clinic System Overview ---\n";
    cout << "Linked List Size: " << petList.size() << "\n";
    cout << "BST Size: " << petTree.size() << "\n";
    cout << "Waiting Queue Size: " << waitingQueue.size() << "\n";
    cout << "Visit Stack Size: " << visitHistory.size() << "\n\n";

    petList.display();
    cout << "\nBST Inorder: ";
    petTree.inorder();
    cout << "BST Preorder: ";
    petTree.preorder();
    cout << "\n";
    waitingQueue.display();
    visitHistory.display();
}

void ClinicOperations::runMenu()
{
    int choice = -1;
    while (choice != 0)
    {
        cout << "\n========== VETERINARY CLINIC MENU ==========\n";
        cout << "1. Register New Pet\n";
        cout << "2. Check In Pet to Waiting Queue (Priority)\n";
        cout << "3. Complete Next Visit (Queue -> Update Record -> Stack)\n";
        cout << "4. Undo / Pop Last Visit Log (Stack)\n";
        cout << "5. Search Pet by ID (BST)\n";
        cout << "6. Search Pet by Name (Linear Search)\n";
        cout << "7. Sort & Display Pets by Name (Insertion Sort)\n";
        cout << "8. Update Pet Record\n";
        cout << "9. Delete Pet Record\n";
        cout << "10. Display Full System Overview\n";
        cout << "0. Exit\n";

        choice = readInt("Choose an option: ");

        switch (choice)
        {
            case 1: registerPetForVisit(); break;
            case 2: checkInPet(); break;
            case 3: completeVisit(); break;
            case 4: undoLastVisit(); break;
            case 5: searchPetById(); break;
            case 6: searchPetByName(); break;
            case 7: sortPetsByName(); break;
            case 8: updatePetRecord(); break;
            case 9: deletePetRecord(); break;
            case 10: displaySystemOverview(); break;
            case 0: cout << "Exiting system. Goodbye!\n"; break;
            default: cout << "Invalid menu option. Try again.\n"; break;
        }
    }
}
