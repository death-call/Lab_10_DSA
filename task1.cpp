
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
};

Node* createNode(int value) {
    Node* newNode = new Node;

    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;

    return newNode;
}

Node* insertBST(Node* root, int value) {
    if (root == nullptr) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insertBST(root->left, value);
    }
    else if (value > root->data) {
        root->right = insertBST(root->right, value);
    }

    return root;
}

// Find inorder successor
Node* findMin(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }

    return root;
}

// BST Deletion
Node* deleteBST(Node* root, int value) {

    if (root == nullptr) {
        return nullptr;
    }

    if (value < root->data) {
        root->left = deleteBST(root->left, value);
    }
    else if (value > root->data) {
        root->right = deleteBST(root->right, value);
    }
    else {

        // Case 1: Leaf node
        if (root->left == nullptr &&
            root->right == nullptr) {

            delete root;
            return nullptr;
        }

        // Case 2: Only right child
        else if (root->left == nullptr) {

            Node* temp = root->right;
            delete root;
            return temp;
        }

        // Case 2: Only left child
        else if (root->right == nullptr) {

            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Case 3: Two children
        else {

            Node* temp = findMin(root->right);

            root->data = temp->data;

            root->right = deleteBST(
                root->right, temp->data
            );
        }
    }

    return root;
}

// Inorder traversal
void inorder(Node* root) {
    if (root == nullptr) {
        return;
    }

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int task1() {

    Node* root = nullptr;

    int values[] = { 50, 30, 70, 20, 40, 60, 80, 65 };

    // Insert values
    for (int i = 0; i < 8; i++) {
        root = insertBST(root, values[i]);
    }

    cout << "Original BST: ";
    inorder(root);

    // Delete 20
    root = deleteBST(root, 20);
    cout << "\nAfter deleting 20: ";
    inorder(root);

    // Delete 60
    root = deleteBST(root, 60);
    cout << "\nAfter deleting 60: ";
    inorder(root);

    // Delete 50
    root = deleteBST(root, 50);
    cout << "\nAfter deleting 50: ";
    inorder(root);

    cout << endl;

    return 0;
}
