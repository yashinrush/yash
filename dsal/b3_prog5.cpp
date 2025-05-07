#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    bool lthread, rthread;  // true if pointer is a thread

    Node(int val) {
        data = val;
        left = right = nullptr;
        lthread = rthread = false;
    }
};

Node *previous = nullptr;

// Utility to create threading
void createThreaded(Node *root) {
    if (!root) return;

    // Left subtree
    createThreaded(root->left);

    // Process this node
    if (!root->left) {
        root->left = previous;
        root->lthread = true;
    }

    if (previous && !previous->right) {
        previous->right = root;
        previous->rthread = true;
    }

    previous = root;

    // Right subtree
    createThreaded(root->right);
}

// Inorder traversal using threads
void inorderThreaded(Node *root) {
    Node *curr = root;
    while (curr && curr->left)
        curr = curr->left;

    while (curr) {
        cout << curr->data << " ";

        // If thread, follow it
        if (curr->rthread)
            curr = curr->right;
        else {
            curr = curr->right;
            while (curr && !curr->lthread)
                curr = curr->left;
        }
    }
}

// Helper to insert nodes (basic BST insert)
Node* insert(Node* root, int key) {
    if (!root) return new Node(key);

    if (key < root->data)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

int main() {
    Node *root = nullptr;
    root = insert(root, 20);
    insert(root, 10);
    insert(root, 30);
    insert(root, 5);
    insert(root, 15);
    insert(root, 25);
    insert(root, 35);

    createThreaded(root);

    cout << "Inorder traversal using threads: ";
    inorderThreaded(root);
    cout << endl;

    return 0;
}
