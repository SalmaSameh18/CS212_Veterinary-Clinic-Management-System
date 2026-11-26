#include <iostream>
#include <string>
#include <limits>
using namespace std;
const int MAX_PETS = 100;

struct Pet {
    int id;
    string name;
    string species;
    int age;
    string owner;
    string phone;
    string gender;
    string medicalNote;
};

// LINKED LIST

class PetList
{
private:

    struct Node
    {
        Pet data;
        Node* next;

        Node(const Pet& p)
        {
            data = p;
            next = nullptr;
        }
    };

    Node* head;
    int count;

public:

    PetList()
    {
        head = nullptr;
        count = 0;
    }

 ~PetList()
    {
        Node* current = head;

        while (current != nullptr)
        {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

int copyToArray(Pet arr[], int capacity) const
{
    int i = 0;
    Node* current = head;

    while (current != nullptr && i < capacity)
    {
        arr[i] = current->data;
        current = current->next;
        i++;
    }

    return i;
}

bool insert(Pet p)
    {
        if (search(p.id) != nullptr)
        {
            return false;
        }

        Node* newNode = new Node(p);

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node* current = head;

            while (current->next != nullptr)
            {
                current = current->next;
            }

            current->next = newNode;
        }

        count++;
        return true;
    }

   
    bool deletePet(int id)
    {
        Node* current = head;
        Node* previous = nullptr;

        while (current != nullptr && current->data.id != id)
        {
            previous = current;
            current = current->next;
        }

        if (current == nullptr)
        {
            return false;
        }

        if (previous == nullptr)
        {
            head = current->next;
        }
        else
        {
            previous->next = current->next;
        }

        delete current;
        count--;

        return true;
    }

    Pet* search(int id)
    {
        Node* current = head;

        while (current != nullptr)
        {
            if (current->data.id == id)
            {
                return &current->data;
            }

            current = current->next;
        }

        return nullptr;
    }

    void display() const
    {
        if (isEmpty())
        {
            cout << "No pet records found.\n";
            return;
        }

        const Node* current = head;

        while (current != nullptr)
        {
            cout << "ID: " << current->data.id << endl;
            cout << "Name: " << current->data.name << endl;
            cout << "Species: " << current->data.species << endl;
            cout << "Age: " << current->data.age << endl;
            cout << "Gender: " << current->data.gender << endl;
            cout << "Owner: " << current->data.owner << endl;
            cout << "Phone: " << current->data.phone << endl;
            cout << "Medical Note: " << current->data.medicalNote << endl;

            cout << "-------------------------\n";

            current = current->next;
        }
    }

    bool isEmpty() const
    {
        return head == nullptr;
    }

    int size() const
    {
        return count;
    }
};

class PetQueue {

private:

    struct Pet {
        int id;
        int priority;
    };

    Pet items[MAX_PETS];
    int count;

public:

    // Constructor
    PetQueue() : count(0) {}

    // Check if queue is empty
    bool isEmpty() const {
        return count == 0;
    }

    // Check if queue is full
    bool isFull() const {
        return count == MAX_PETS;
    }

    // Return number of pets
    int size() const {
        return count;
    }

    // Add pet according to priority
    bool enqueue(int id, int priority = 0) {

        if (isFull())
            return false;

        int i = count - 1;

        while (i >= 0 && items[i].priority < priority) {
            items[i + 1] = items[i];
            --i;
        }

        items[i + 1].id = id;
        items[i + 1].priority = priority;

        ++count;

        return true;
    }

    // Remove pet from front
    bool dequeue(int& id) {

        if (isEmpty())
            return false;

        id = items[0].id;

        for (int i = 0; i < count - 1; ++i) {
            items[i] = items[i + 1];
        }

        --count;

        return true;
    }

    // Get front pet
    bool front(int& id) const {

        if (isEmpty())
            return false;

        id = items[0].id;

        return true;
    }

    // Get rear pet
    bool rear(int& id) const {

        if (isEmpty())
            return false;

        id = items[count - 1].id;

        return true;
    }

    // Search for a pet by ID
    bool contains(int id) const {

        for (int i = 0; i < count; ++i) {

            if (items[i].id == id)
                return true;
        }

        return false;
    }

    // Remove pet by ID
    bool removeById(int id) {

        for (int i = 0; i < count; ++i) {

            if (items[i].id == id) {

                for (int j = i; j < count - 1; ++j) {
                    items[j] = items[j + 1];
                }

                --count;

                return true;
            }
        }

        return false;
    }

    // Display all pets
    void display() const {

        if (isEmpty()) {
            cout << "Waiting queue is empty.\n";
            return;
        }

        cout << "Waiting pets (Highest to Lowest Priority):\n";

        for (int i = 0; i < count; ++i) {

            cout << " - Pet ID: " << items[i].id
                 << " | Priority: " << items[i].priority
                 << '\n';
        }
    }

}; // End of class


class VisitStack {

private:
    string items[MAX_PETS];
    int topIndex;

public:

    VisitStack() : topIndex(-1) {}

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex == MAX_PETS - 1;
    }

    int size() const {
        return topIndex + 1;
    }

    bool push(const string& visitor) {

        if (isFull()) {
            cout << "Stack is full. Cannot push " << visitor << endl;
            return false;
        }

        items[++topIndex] = visitor;
        return true;
    }

    bool pop(string& visitor) {

        if (isEmpty()) {
            cout << "Stack is empty. Cannot pop." << endl;
            return false;
        }

        visitor = items[topIndex--];
        return true;
    }

    bool peek(string& visitor) const {

        if (isEmpty()) {
            cout << "Stack is empty. Cannot peek." << endl;
            return false;
        }

        visitor = items[topIndex];
        return true;
    }

    void display() const {

        if (isEmpty()) {
            cout << "No completed visits yet.\n";
            return;
        }

        cout << "Recent visits (newest first):\n";

        for (int i = topIndex; i >= 0; --i) {
            cout << " - " << items[i] << "\n";
        }
    }

    void clear() {
        topIndex = -1;
    }

};

class PetBST {
private:

    struct Node {
        Pet data;
        Node* left;
        Node* right;

        Node(const Pet& p) {
            data = p;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;
    int count;

    // Insert a new pet recursively
    Node* insertNode(Node* node, const Pet& p, bool& inserted) {

        if (node == nullptr) {
            inserted = true;
            return new Node(p);
        }

        if (p.id < node->data.id) {
            node->left = insertNode(node->left, p, inserted);
        }

        else if (p.id > node->data.id) {
            node->right = insertNode(node->right, p, inserted);
        }

        else {
            inserted = false;
        }

        return node;
    }

    // Search recursively
    Node* searchNode(Node* node, int id) const {

        if (node == nullptr || node->data.id == id) {
            return node;
        }

        if (id < node->data.id) {
            return searchNode(node->left, id);
        }

        return searchNode(node->right, id);
    }

    // Find the smallest node in a subtree
    Node* findMin(Node* node) const {

        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }

        return node;
    }

    // Delete a pet recursively
    Node* deleteNode(Node* node, int id, bool& deleted) {

        if (node == nullptr) {
            return nullptr;
        }

        if (id < node->data.id) {
            node->left = deleteNode(node->left, id, deleted);
        }

        else if (id > node->data.id) {
            node->right = deleteNode(node->right, id, deleted);
        }

        else {

            deleted = true;

            // Case 1: No children
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            // Case 2: Only right child
            else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            // Case 2: Only left child
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: Two children
            else {

                Node* successor = findMin(node->right);

                node->data = successor->data;

                bool ignored = false;

                node->right = deleteNode(
                    node->right,
                    successor->data.id,
                    ignored
                );
            }
        }

        return node;
    }

    // Inorder: Left, Root, Right
    void inorderTraversal(Node* node) const {

        if (node == nullptr) {
            return;
        }

        inorderTraversal(node->left);

        cout << "ID: " << node->data.id
             << " | Name: " << node->data.name << endl;

        inorderTraversal(node->right);
    }

    // Preorder: Root, Left, Right
    void preorderTraversal(Node* node) const {

        if (node == nullptr) {
            return;
        }

        cout << "ID: " << node->data.id
             << " | Name: " << node->data.name << endl;

        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }

    // Delete all nodes recursively
    void clearTree(Node* node) {

        if (node == nullptr) {
            return;
        }

        clearTree(node->left);
        clearTree(node->right);

        delete node;
    }

public:

    // Constructor
    PetBST() {
        root = nullptr;
        count = 0;
    }

    // Destructor
    ~PetBST() {
        clear();
    }

    // Check if the tree is empty
    bool isEmpty() const {
        return root == nullptr;
    }

    // Return number of pets
    int size() const {
        return count;
    }

    // Insert a pet
    bool insert(const Pet& p) {

        bool inserted = false;

        root = insertNode(root, p, inserted);

        if (inserted) {
            count++;
        }

        else {
            cout << "Pet ID already exists.\n";
        }

        return inserted;
    }

    // Search for a pet
    Pet* search(int id) const {

        Node* result = searchNode(root, id);

        if (result == nullptr) {
            return nullptr;
        }

        return &(result->data);
    }

    // Delete a pet
    bool deletePet(int id) {

        bool deleted = false;

        root = deleteNode(root, id, deleted);

        if (deleted) {
            count--;
        }

        else {
            cout << "Pet not found.\n";
        }

        return deleted;
    }

    // Update pet information without changing ID
    bool updatePet(int id, const Pet& updatedPet) {

        Pet* foundPet = search(id);

        if (foundPet == nullptr) {
            cout << "Pet not found.\n";
            return false;
        }

        if (updatedPet.id != id) {
            cout << "Pet ID cannot be changed.\n";
            return false;
        }

        *foundPet = updatedPet;

        return true;
    }

    // Display pets sorted by ID
    void inorder() const {

        if (isEmpty()) {
            cout << "Tree is empty.\n";
            return;
        }

        cout << "\nPets in Ascending ID Order:\n";

        inorderTraversal(root);
    }

    // Display tree structure order
    void preorder() const {

        if (isEmpty()) {
            cout << "Tree is empty.\n";
            return;
        }

        cout << "\nPreorder Traversal:\n";

        preorderTraversal(root);
    }

    // Clear the entire tree
    void clear() {

        clearTree(root);

        root = nullptr;
        count = 0;
    }
};

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
