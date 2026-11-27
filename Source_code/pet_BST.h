#ifndef PET_BST_H
#define PET_BST_H

#include "../Main/Pet.h"

using namespace std;

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

#endif // PET_BST_H
