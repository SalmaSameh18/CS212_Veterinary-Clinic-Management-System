#include "Pet.h"
#include "../Linked_List/Pet_List.h"
#include "../BST/pet_BST.h"
#include "../Queue/Pet_Queue.h"
#include "../Stack/Pet_Stack.h"
#include "../Clinic_Operations/Pet_Clinic_Operations.h"

using namespace std;

int main()
{
    PetList petList;
    PetBST petTree;
    PetQueue waitingQueue;
    VisitStack visitHistory;

    ClinicOperations clinic(petList, petTree, waitingQueue, visitHistory);
    clinic.runMenu();

    return 0;
}
