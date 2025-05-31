#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Build Complete Binary Tree from vector
Node* buildCBT(const vector<int>& elements) {
    if (elements.empty()) return nullptr;

    Node* root = new Node(elements[0]);
    queue<Node*> q;
    q.push(root);

    int i = 1;
    while (i < (int)elements.size()) {
        Node* current = q.front();
        q.pop();

        if (i < (int)elements.size()) {
            current->left = new Node(elements[i++]);
            q.push(current->left);
        }
        if (i < (int)elements.size()) {
            current->right = new Node(elements[i++]);
            q.push(current->right);
        }
    }

    return root;
}

void inorderTraversal(Node* root) {
    if (!root) return;
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

void preorderTraversal(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void postorderTraversal(Node* root) {
    if (!root) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->data << " ";
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> elements(n);
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> elements[i];
    }

    Node* root = buildCBT(elements);

    cout << "Inorder traversal: ";
    inorderTraversal(root);
    cout << "\n";

    cout << "Preorder traversal: ";
    preorderTraversal(root);
    cout << "\n";

    cout << "Postorder traversal: ";
    postorderTraversal(root);
    cout << "\n";

    return 0;
}
