#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

// Node definition
struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char val) : data(val), left(nullptr), right(nullptr) {}
};

// Check if operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Build expression tree from postfix
Node* constructTree(string postfix) {
    stack<Node*> st;
    for (char ch : postfix) {
        if (isalnum(ch)) {
            st.push(new Node(ch));
        } else if (isOperator(ch)) {
            Node* node = new Node(ch);
            node->right = st.top(); st.pop();
            node->left = st.top(); st.pop();
            st.push(node);
        }
    }
    return st.top();
}

// Recursive inorder traversal
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// Non-recursive postorder traversal using two stacks
void postorderNonRecursive(Node* root) {
    if (root == nullptr)
        return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* curr = s1.top(); s1.pop();
        s2.push(curr);

        if (curr->left)
            s1.push(curr->left);
        if (curr->right)
            s1.push(curr->right);
    }

    // Print postorder
    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

int main() {
    string infix = "a-b*c-d/e+f";
    string postfix = "abc*-de/-f+";

    // Step 1: Construct expression tree
    Node* root = constructTree(postfix);

    cout << "Inorder traversal (infix): ";
    inorder(root);
    cout << endl;

    cout << "Postorder traversal (non-recursive): ";
    postorderNonRecursive(root);
    cout << endl;

    return 0;
}
