#include "pet_main.h"
#include <iostream>
#include <limits>

using namespace std;

// ============================================================================
// 1. PetList Implementation (Singly Linked List)
// ============================================================================
PetList::Node::Node(const Pet& p)
{
    data = p;
    next = nullptr;
}

PetList::PetList()
{
    head = nullptr;
    count = 0;
}

PetList::~PetList()
{
    Node* curr = head;
    while (curr != nullptr)
    {
        Node* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    head = nullptr;
    count = 0;
}

int PetList::copyToArray(Pet arr[], int capacity) const
{
    int copied = 0;
    Node* curr = head;
    while (curr != nullptr && copied < capacity)
    {
        arr[copied] = curr->data;
        copied++;
        curr = curr->next;
    }
    return copied;
}

bool PetList::insert(const Pet& p)
{
    if (count >= MAX_PETS)
    {
        return false; // Capacity limit reached
    }
    if (search(p.id) != nullptr)
    {
        return false; // Duplicate ID not allowed
    }

    Node* newNode = new Node(p);
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node* temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    count++;
    return true;
}

bool PetList::deletePet(int id)
{
    if (head == nullptr)
    {
        return false;
    }

    Node* curr = head;
    Node* prev = nullptr;

    while (curr != nullptr && curr->data.id != id)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr)
    {
        return false; // Not found
    }

    if (prev == nullptr)
    {
        head = curr->next;
    }
    else
    {
        prev->next = curr->next;
    }

    delete curr;
    count--;
    return true;
}

bool PetList::updatePet(int id, const Pet& updatedPet)
{
    Pet* target = search(id);
    if (target == nullptr)
    {
        return false;
    }

    // Keep the original ID consistent
    Pet temp = updatedPet;
    temp.id = id;
    *target = temp;
    return true;
}

Pet* PetList::search(int id)
{
    Node* curr = head;
    while (curr != nullptr)
    {
        if (curr->data.id == id)
        {
            return &(curr->data);
        }
        curr = curr->next;
    }
    return nullptr;
}

void PetList::display() const
{
    if (isEmpty())
    {
        cout << "No pet records in the linked list.\n";
        return;
    }

    Node* curr = head;
    int idx = 1;
    while (curr != nullptr)
    {
        cout << idx++ << ". [ID: " << curr->data.id << "] "
             << curr->data.name << " | Species: " << curr->data.species
             << " | Age: " << curr->data.age << " | Gender: " << curr->data.gender << "\n"
             << "   Owner: " << curr->data.owner << " (" << curr->data.phone << ")\n"
             << "   Note: " << curr->data.medicalNote << "\n";
        curr = curr->next;
    }
}

bool PetList::isEmpty() const
{
    return head == nullptr;
}

int PetList::size() const
{
    return count;
}

// ============================================================================
// 2. PetBST Implementation (Binary Search Tree keyed by Pet ID)
// ============================================================================
PetBST::Node::Node(const Pet& p)
{
    data = p;
    left = nullptr;
    right = nullptr;
}

PetBST::PetBST()
{
    root = nullptr;
    count = 0;
}

PetBST::~PetBST()
{
    clear();
}

PetBST::Node* PetBST::insertNode(Node* node, const Pet& p, bool& inserted)
{
    if (node == nullptr)
    {
        inserted = true;
        return new Node(p);
    }

    if (p.id < node->data.id)
    {
        node->left = insertNode(node->left, p, inserted);
    }
    else if (p.id > node->data.id)
    {
        node->right = insertNode(node->right, p, inserted);
    }
    else
    {
        // Duplicate ID is ignored
        inserted = false;
    }
    return node;
}

PetBST::Node* PetBST::searchNode(Node* node, int id) const
{
    if (node == nullptr || node->data.id == id)
    {
        return node;
    }
    if (id < node->data.id)
    {
        return searchNode(node->left, id);
    }
    return searchNode(node->right, id);
}

PetBST::Node* PetBST::findMin(Node* node) const
{
    while (node != nullptr && node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

PetBST::Node* PetBST::deleteNode(Node* node, int id, bool& deleted)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (id < node->data.id)
    {
        node->left = deleteNode(node->left, id, deleted);
    }
    else if (id > node->data.id)
    {
        node->right = deleteNode(node->right, id, deleted);
    }
    else
    {
        deleted = true;

        // Case 1 & 2: Zero or one child
        if (node->left == nullptr)
        {
            Node* rightChild = node->right;
            delete node;
            return rightChild;
        }
        if (node->right == nullptr)
        {
            Node* leftChild = node->left;
            delete node;
            return leftChild;
        }

        // Case 3: Two children -> replace with inorder successor
        Node* successor = findMin(node->right);
        node->data = successor->data;
        bool dummy = false;
        node->right = deleteNode(node->right, successor->data.id, dummy);
    }

    return node;
}

void PetBST::inorderTraversal(Node* node) const
{
    if (node == nullptr) return;
    inorderTraversal(node->left);
    cout << "[ID: " << node->data.id << " - " << node->data.name << "] ";
    inorderTraversal(node->right);
}

void PetBST::preorderTraversal(Node* node) const
{
    if (node == nullptr) return;
    cout << "[ID: " << node->data.id << " - " << node->data.name << "] ";
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

void PetBST::clearTree(Node* node)
{
    if (node == nullptr) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

bool PetBST::isEmpty() const
{
    return root == nullptr;
}

int PetBST::size() const
{
    return count;
}

bool PetBST::insert(const Pet& p)
{
    bool inserted = false;
    root = insertNode(root, p, inserted);
    if (inserted)
    {
        count++;
    }
    return inserted;
}

Pet* PetBST::search(int id) const
{
    Node* found = searchNode(root, id);
    if (found == nullptr)
    {
        return nullptr;
    }
    return &(found->data);
}

bool PetBST::deletePet(int id)
{
    bool deleted = false;
    root = deleteNode(root, id, deleted);
    if (deleted)
    {
        count--;
    }
    return deleted;
}

bool PetBST::updatePet(int id, const Pet& updatedPet)
{
    Node* target = searchNode(root, id);
    if (target == nullptr)
    {
        return false;
    }

    // Preserve ID so BST ordering remains valid
    Pet temp = updatedPet;
    temp.id = id;
    target->data = temp;
    return true;
}

void PetBST::inorder() const
{
    if (isEmpty())
    {
        cout << "BST is empty.\n";
        return;
    }
    inorderTraversal(root);
    cout << "\n";
}

void PetBST::preorder() const
{
    if (isEmpty())
    {
        cout << "BST is empty.\n";
        return;
    }
    preorderTraversal(root);
    cout << "\n";
}

void PetBST::clear()
{
    clearTree(root);
    root = nullptr;
    count = 0;
}

// ============================================================================
// 3. PetQueue Implementation (Priority Queue: higher priority number first)
// ============================================================================
PetQueue::PetQueue()
{
    count = 0;
}

bool PetQueue::isEmpty() const
{
    return count == 0;
}

bool PetQueue::isFull() const
{
    return count >= MAX_PETS;
}

int PetQueue::size() const
{
    return count;
}

// Higher priority value comes closer to the front (index 0); ties stay FIFO
bool PetQueue::enqueue(int id, int priority)
{
    if (isFull())
    {
        return false;
    }

    int pos = count;
    while (pos > 0 && items[pos - 1].priority < priority)
    {
        items[pos] = items[pos - 1];
        pos--;
    }

    items[pos].id = id;
    items[pos].priority = priority;
    count++;
    return true;
}

bool PetQueue::dequeue(int& id)
{
    if (isEmpty())
    {
        return false;
    }

    id = items[0].id;
    for (int i = 0; i < count - 1; i++)
    {
        items[i] = items[i + 1];
    }
    count--;
    return true;
}

bool PetQueue::front(int& id) const
{
    if (isEmpty())
    {
        return false;
    }
    id = items[0].id;
    return true;
}

bool PetQueue::rear(int& id) const
{
    if (isEmpty())
    {
        return false;
    }
    id = items[count - 1].id;
    return true;
}

bool PetQueue::contains(int id) const
{
    for (int i = 0; i < count; i++)
    {
        if (items[i].id == id)
        {
            return true;
        }
    }
    return false;
}

bool PetQueue::removeById(int id)
{
    int foundIdx = -1;
    for (int i = 0; i < count; i++)
    {
        if (items[i].id == id)
        {
            foundIdx = i;
            break;
        }
    }

    if (foundIdx == -1)
    {
        return false;
    }

    for (int i = foundIdx; i < count - 1; i++)
    {
        items[i] = items[i + 1];
    }
    count--;
    return true;
}

void PetQueue::display() const
{
    if (isEmpty())
    {
        cout << "Waiting queue is empty.\n";
        return;
    }

    cout << "Waiting Queue (Front -> Rear): ";
    for (int i = 0; i < count; i++)
    {
        cout << "[ID: " << items[i].id << ", P:" << items[i].priority << "]";
        if (i < count - 1)
        {
            cout << " -> ";
        }
    }
    cout << "\n";
}

// ============================================================================
// 4. VisitStack Implementation (Stack - LIFO)
// ============================================================================
VisitStack::VisitStack()
{
    topIndex = -1;
}

bool VisitStack::isEmpty() const
{
    return topIndex == -1;
}

bool VisitStack::isFull() const
{
    return topIndex >= MAX_PETS - 1;
}

int VisitStack::size() const
{
    return topIndex + 1;
}

bool VisitStack::push(const string& visitor)
{
    if (isFull())
    {
        return false;
    }
    topIndex++;
    items[topIndex] = visitor;
    return true;
}

bool VisitStack::pop(string& visitor)
{
    if (isEmpty())
    {
        return false;
    }
    visitor = items[topIndex];
    topIndex--;
    return true;
}

bool VisitStack::peek(string& visitor) const
{
    if (isEmpty())
    {
        return false;
    }
    visitor = items[topIndex];
    return true;
}

void VisitStack::display() const
{
    if (isEmpty())
    {
        cout << "Visit history stack is empty.\n";
        return;
    }

    cout << "Visit History (Most Recent First):\n";
    for (int i = topIndex; i >= 0; i--)
    {
        cout << "  - " << items[i] << "\n";
    }
}

void VisitStack::clear()
{
    topIndex = -1;
}

// ============================================================================
// 5. ClinicOperations Implementation (Workflows & Menu)
// ============================================================================
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

// Why: BST search is chosen for ID lookup because Pet ID is a unique key,
// giving O(log n) average lookup time (O(n) worst case if skewed) instead of
// scanning all records sequentially.
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

// Why: Linear search is chosen for name lookup because pet names are not
// unique and are not used as the BST key, so multiple pets can share a name
// and we must inspect all matching records in O(n) time without requiring pre-sorting.
void ClinicOperations::searchPetByName() const
{
    string target = readLine("Enter Pet Name to search (Linear Search): ");
    Pet tempArr[MAX_PETS];
    int n = petList.copyToArray(tempArr, MAX_PETS);

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

// Why: Insertion sort is chosen for sorting pets by name because the clinic
// dataset is relatively small (up to MAX_PETS = 100), it is simple to implement
// and trace in class, works well on small/nearly-sorted lists in-place on the
// copied array, and preserves relative order (stable sort) for equal names.
void ClinicOperations::sortPetsByName() const
{
    Pet arr[MAX_PETS];
    int n = petList.copyToArray(arr, MAX_PETS);
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

// ============================================================================
// 6. Main Entry Point
// ============================================================================
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
