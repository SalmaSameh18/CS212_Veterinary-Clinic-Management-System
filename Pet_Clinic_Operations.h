#ifndef PET_CLINIC_OPERATIONS_H
#define PET_CLINIC_OPERATIONS_H

#include <string>
#include "Pet.h"
#include "Pet_List.h"
#include "pet_BST.h"
#include "Pet_Queue.h"
#include "Pet_Stack.h"

using namespace std;

class ClinicOperations
{
private:
    static const int MAX_CLINIC_PETS = 100;

    PetList& petList;
    PetBST& petTree;
    PetQueue& waitingQueue;
    VisitStack& visitHistory;

    int readInt(const string& prompt) const;
    string readLine(const string& prompt) const;

public:
    ClinicOperations(PetList& list, PetBST& tree,
                     PetQueue& queue, VisitStack& history);

    bool validatePetID(int id) const;
    bool validatePetInput(const Pet& p) const;

    bool registerPetForVisit();
    bool updatePetRecord();
    bool deletePetRecord();
    bool checkInPet();
    bool completeVisit();
    void sortPetsByName() const;

    bool undoLastVisit();
    void searchPetById() const;
    void searchPetByName() const;
    void displaySystemOverview() const;
    void runMenu();
};

#endif // PET_CLINIC_OPERATIONS_H