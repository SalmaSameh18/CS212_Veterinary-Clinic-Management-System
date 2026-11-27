#include "PetBST.h"
#include <iostream>

using namespace std;

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
