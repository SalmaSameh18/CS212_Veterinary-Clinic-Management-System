#ifndef PET_MAIN_H
#define PET_MAIN_H

#include <string>
#include "Pet.h" // Ensures Pet struct/class is available

using namespace std;

// ============================================================================
// Global Constants
// ============================================================================
const int MAX_PETS = 100;

// ============================================================================
// 1. PetList (Singly Linked List for storing Pet Medical Records)
// ============================================================================
class PetList
{
private:
    struct Node
    {
        Pet data;
        Node* next;

        Node(const Pet& p);
    };

    Node* head;
    int count;

public:
    PetList();
    ~PetList();

    // Copies current records into a caller-provided array (for sorting/searching)
    int copyToArray(Pet arr[], int capacity) const;

    bool insert(const Pet& p);
    bool deletePet(int id);
    bool updatePet(int id, const Pet& updatedPet);
    Pet* search(int id);

    void display() const;

    bool isEmpty() const;
    int size() const;
};

// ============================================================================
// 2. PetBST (Binary Search Tree for fast ID lookup & sorted traversal)
// ============================================================================
class PetBST
{
private:
    struct Node
    {
        Pet data;
        Node* left;
        Node* right;

        Node(const Pet& p);
    };

    Node* root;
    int count;

    // Recursive helper functions
    Node* insertNode(Node* node, const Pet& p, bool& inserted);
    Node* searchNode(Node* node, int id) const;
    Node* findMin(Node* node) const;
    Node* deleteNode(Node* node, int id, bool& deleted);
    void inorderTraversal(Node* node) const;
    void preorderTraversal(Node* node) const;
    void clearTree(Node* node);

public:
    PetBST();
    ~PetBST();

    bool isEmpty() const;
    int size() const;

    bool insert(const Pet& p);
    Pet* search(int id) const;
    bool deletePet(int id);
    bool updatePet(int id, const Pet& updatedPet);

    void inorder() const;
    void preorder() const;
    void clear();
};

// ============================================================================
// 3. PetQueue (Priority Queue for waiting room management)
// ============================================================================
class PetQueue
{
private:
    struct QueueItem
    {
        int id;
        int priority;
    };

    QueueItem items[MAX_PETS];
    int count;

public:
    PetQueue();

    bool isEmpty() const;
    bool isFull() const;
    int size() const;

    // Inserts item according to priority
    bool enqueue(int id, int priority = 0);
    bool dequeue(int& id);
    bool front(int& id) const;
    bool rear(int& id) const;

    bool contains(int id) const;
    bool removeById(int id);

    void display() const;
};

// ============================================================================
// 4. VisitStack (Stack for tracking recent visit history - LIFO)
// ============================================================================
class VisitStack
{
private:
    string items[MAX_PETS];
    int topIndex;

public:
    VisitStack();

    bool isEmpty() const;
    bool isFull() const;
    int size() const;

    bool push(const string& visitor);
    bool pop(string& visitor);
    bool peek(string& visitor) const;

    void display() const;
    void clear();
};

// ============================================================================
// 5. ClinicOperations (Controller class coordinating all data structures)
// ============================================================================
class ClinicOperations
{
private:
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

#endif // PET_MAIN_H
