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
