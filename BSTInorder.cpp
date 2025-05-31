#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* left;
    Node* right;

    // Constructor to initialize node
    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};

// Function to insert a node into the Binary Tree
Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value); // Create a new node if tree is empty
    }

    // Insert in left subtree if value is smaller
    if (value < root->data) {
        root->left = insert(root->left, value);
    }
    // Insert in right subtree if value is greater
    else {
        root->right = insert(root->right, value);
    }

    return root;
}

// Inorder traversal (Left - Root - Right)
void inorderTraversal(Node* root) {
    if (root == nullptr)
        return;

    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

// Main function
int main() {
    Node* root = nullptr; // Initialize root node

    // Insert values into the Binary Tree
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    // Print Inorder Traversal (Sorted Order)
    cout << "Inorder Traversal of Binary Tree: ";
    inorderTraversal(root);

    return 0;
}
