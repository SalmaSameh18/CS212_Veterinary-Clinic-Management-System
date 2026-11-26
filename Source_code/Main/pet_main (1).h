#ifndef PET_MAIN_H
#define PET_MAIN_H

#include <string>
#include "Pet.h" // Make sure Pet.h (defining class/struct Pet) is included before this file or exists in the same directory

using namespace std;

// ============================================================================
// Global Constants
// ============================================================================
const int MAX_PETS = 100;

// ============================================================================
// 1. PetList (Singly Linked List for storing Pets)
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

    int copyToArray(Pet arr[], int capacity) const;

    bool insert(Pet p);
    bool deletePet(int id);
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

    // Insert a new pet recursively
    Node* insertNode(Node* node, const Pet& p, bool& inserted);

    // Search recursively
    Node* searchNode(Node* node, int id) const;

    // Find the smallest node in a subtree
    Node* findMin(Node* node) const;

    // Delete a pet recursively
    Node* deleteNode(Node* node, int id, bool& deleted);

    // Inorder: Left, Root, Right
    void inorderTraversal(Node* node) const;

    // Preorder: Root, Left, Right
    void preorderTraversal(Node* node) const;

    // Delete all nodes recursively
    void clearTree(Node* node);

public:
    // Constructor & Destructor
    PetBST();
    ~PetBST();

    // Check if the tree is empty
    bool isEmpty() const;

    // Return number of pets
    int size() const;

    // Insert a pet
    bool insert(const Pet& p);

    // Search for a pet
    Pet* search(int id) const;

    // Delete a pet
    bool deletePet(int id);

    // Update pet information without changing ID
    bool updatePet(int id, const Pet& updatedPet);

    // Display pets sorted by ID
    void inorder() const;

    // Display tree structure order
    void preorder() const;

    // Clear the entire tree
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
    // Constructor
    PetQueue();

    // Check if queue is empty
    bool isEmpty() const;

    // Check if queue is full
    bool isFull() const;

    // Return number of pets
    int size() const;

    // Add pet according to priority
    bool enqueue(int id, int priority = 0);

    // Remove pet from front
    bool dequeue(int& id);

    // Get front pet
    bool front(int& id) const;

    // Get rear pet
    bool rear(int& id) const;

    // Search for a pet by ID
    bool contains(int id) const;

    // Remove pet by ID
    bool removeById(int id);

    // Display all pets
    void display() const;
};

// ============================================================================
// 4. VisitStack (Stack for tracking visit history)
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

#endif // PET_MAIN_H
