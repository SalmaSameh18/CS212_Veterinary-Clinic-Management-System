#include "pet_main.h"

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