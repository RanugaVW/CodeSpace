//Swap nodes to a given k
#include <vector>
using namespace std;

struct Node {
    int index;
    int depth;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int idx, int d) : index(idx), depth(d) {}
};

// Build the tree recursively
void buildTree(Node* root, const vector<vector<int>>& indexes) {
    int i = root->index - 1;
    int leftChild = indexes[i][0];
    int rightChild = indexes[i][1];

    if (leftChild != -1) {
        root->left = new Node(leftChild, root->depth + 1);
        buildTree(root->left, indexes);
    }
    if (rightChild != -1) {
        root->right = new Node(rightChild, root->depth + 1);
        buildTree(root->right, indexes);
    }
}

// Swap children at all depths multiples of k
void swapAtDepth(Node* root, int k) {
    if (!root) return;

    if (root->depth % k == 0) {
        Node* temp = root->left;
        root->left = root->right;
        root->right = temp;
    }

    swapAtDepth(root->left, k);
    swapAtDepth(root->right, k);
}

// In-order traversal filling the vector
void inorder(Node* root, vector<int>& traversal) {
    if (!root) return;

    inorder(root->left, traversal);
    traversal.push_back(root->index);
    inorder(root->right, traversal);
}

vector<vector<int>> swapNodes(vector<vector<int>> indexes, vector<int> queries) {
    // Build tree rooted at 1, depth 1
    Node* root = new Node(1, 1);
    buildTree(root, indexes);

    vector<vector<int>> result;

    // For each query k, perform swaps and collect in-order traversal
    for (int k : queries) {
        swapAtDepth(root, k);

        vector<int> traversal;
        inorder(root, traversal);

        result.push_back(traversal);
    }

    return result;
}