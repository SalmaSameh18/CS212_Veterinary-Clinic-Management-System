#ifndef CLINICOPERATIONS_H
#define CLINICOPERATIONS_H

#include "Pet.h"
#include "PetList.h"
#include "PetBST.h"
#include "PetQueue.h"
#include "VisitStack.h"

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
    PetQueue& queue, VisitStack& history);

// 1. Validate Pet ID
bool validatePetID(int id);

// 2. Validate Pet Input
bool validatePetInput(const Pet& p);

// 3. Register Pet For Visit
bool registerPetForVisit();

// 4. Check In Pet
bool checkInPet();

// 5. Complete Visit
bool completeVisit();

// 6. Sort Pets By Name
void sortPetsByName();
};

#endif
