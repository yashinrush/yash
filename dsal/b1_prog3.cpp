#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// Insert a new node
Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }
    if (key < root->data)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

// Inorder traversal
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// Find number of nodes in the longest path (height)
int longestPath(Node* root) {
    if (root == nullptr)
        return 0;

    int leftHeight = longestPath(root->left);
    int rightHeight = longestPath(root->right);

    return max(leftHeight, rightHeight) + 1;
}

// Find minimum value in the tree
int findMin(Node* root) {
    Node* current = root;
    while (current && current->left != nullptr)
        current = current->left;

    return current->data;
}

// Mirror the tree (swap left and right at every node)
void mirror(Node* root) {
    if (root == nullptr)
        return;

    mirror(root->left);
    mirror(root->right);

    swap(root->left, root->right);
}

// Search for a value
bool search(Node* root, int key) {
    if (root == nullptr)
        return false;
    if (root->data == key)
        return true;
    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

int main() {
    Node* root = nullptr;
    int values[] = {20, 10, 30, 5, 15, 25, 35};
    int n = sizeof(values) / sizeof(values[0]);

    // Construct the BST
    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }

    cout << "Inorder traversal: ";
    inorder(root);
    cout << endl;

    // Insert new node
    int newNode = 12;
    root = insert(root, newNode);
    cout << "After inserting " << newNode << ", inorder: ";
    inorder(root);
    cout << endl;

    // Find number of nodes in longest path
    int height = longestPath(root);
    cout << "Number of nodes in longest path (height): " << height << endl;

    // Minimum data value
    int minVal = findMin(root);
    cout << "Minimum value in the tree: " << minVal << endl;

    // Mirror the tree
    mirror(root);
    cout << "Inorder after mirroring: ";
    inorder(root);
    cout << endl;

    // Search for a value
    int key = 25;
    bool found = search(root, key);
    if (found)
        cout << key << " is found in the tree." << endl;
    else
        cout << key << " is NOT found in the tree." << endl;

    return 0;
}
