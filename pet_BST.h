#ifndef PET_BST_H
#define PET_BST_H
#include "Pet.h"

class PetBST {
private:

    struct Node {
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

    // Constructor
    PetBST();

    // Destructor
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

#endif
