#ifndef PET_CLINIC_OPERATIONS_H
#define PET_CLINIC_OPERATIONS_H

#include <string>
#include "../Main/Pet.h"
#include "../Linked_List/Pet_List.h"
#include "../BST/pet_BST.h"
#include "../Queue/Pet_Queue.h"
#include "../Stack/Pet_Stack.h"

using namespace std;

class ClinicOperations
{
private:
    static const int MAX_CLINIC_PETS = 100;

    PetList& petList;
    PetBST& petTree;
    PetQueue& waitingQueue;
    VisitStack& visitHistory;

    // Input helper functions for safe console reading
    int readInt(const string& prompt) const;
    string readLine(const string& prompt) const;

public:
    ClinicOperations(PetList& list, PetBST& tree,
                     PetQueue& queue, VisitStack& history);

    // 1. Validate Pet ID
    bool validatePetID(int id) const;

    // 2. Validate Pet Input
    bool validatePetInput(const Pet& p) const;

    // 3. Register Pet For Visit
    bool registerPetForVisit();

    // Update & Delete Pet Records
    bool updatePetRecord();
    bool deletePetRecord();

    // 4. Check In Pet
    bool checkInPet();

    // 5. Complete Visit
    bool completeVisit();

    // 6. Sort Pets By Name
    void sortPetsByName() const;

    // Extra clinic helpers & menu
    bool undoLastVisit();
    void searchPetById() const;
    void searchPetByName() const;
    void displaySystemOverview() const;
    void runMenu();
};

#endif // PET_CLINIC_OPERATIONS_H
