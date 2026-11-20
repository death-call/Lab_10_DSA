
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
};

// Get height of a node
int getHeight(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    return root->height;
}

// Calculate balance factor
int getBalance(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    return getHeight(root->left) - getHeight(root->right);
}

// Create a new node
Node* createNode(int value) {
    Node* newNode = new Node;

    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;

    return newNode;
}

// Right rotation
Node* rightRotate(Node* root) {

    Node* newRoot = root->left;
    Node* temp = newRoot->right;

    // Perform rotation
    newRoot->right = root;
    root->left = temp;

    // Update heights: old root first
    root->height = 1 + max(
        getHeight(root->left),
        getHeight(root->right)
    );

    newRoot->height = 1 + max(
        getHeight(newRoot->left),
        getHeight(newRoot->right)
    );

    return newRoot;
}

// Left rotation
Node* leftRotate(Node* root) {

    Node* newRoot = root->right;
    Node* temp = newRoot->left;

    // Perform rotation
    newRoot->left = root;
    root->right = temp;

    // Update heights: old root first
    root->height = 1 + max(
        getHeight(root->left),
        getHeight(root->right)
    );

    newRoot->height = 1 + max(
        getHeight(newRoot->left),
        getHeight(newRoot->right)
    );

    return newRoot;
}

// AVL insertion
Node* insertAVL(Node* root, int value) {

    // Step 1: Normal BST insertion
    if (root == nullptr) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insertAVL(root->left, value);
    }
    else if (value > root->data) {
        root->right = insertAVL(root->right, value);
    }
    else {
        return root;
    }

    // Step 2: Update height
    root->height = 1 + max(
        getHeight(root->left),
        getHeight(root->right)
    );

    // Step 3: Calculate balance factor
    int balance = getBalance(root);

    // Case 1: LL
    if (balance > 1 && value < root->left->data) {
        return rightRotate(root);
    }

    // Case 2: RR
    if (balance < -1 && value > root->right->data) {
        return leftRotate(root);
    }

    // Case 3: LR
    if (balance > 1 && value > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Case 4: RL
    if (balance < -1 && value < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Preorder traversal
void preorder(Node* root) {
    if (root == nullptr) {
        return;
    }

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
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

// Display balance factors to verify balance
void displayBalance(Node* root) {
    if (root == nullptr) {
        return;
    }

    cout << "Node " << root->data
        << " | Height: " << root->height
        << " | Balance Factor: " << getBalance(root)
        << endl;

    displayBalance(root->left);
    displayBalance(root->right);
}

// Free memory
void destroyTree(Node* root) {
    if (root == nullptr) {
        return;
    }

    destroyTree(root->left);
    destroyTree(root->right);

    delete root;
}

int task2
() {

    int sequences[4][3] = {
        {30, 20, 10},
        {10, 20, 30},
        {30, 10, 20},
        {10, 30, 20}
    };

    string cases[4] = {
        "LL Case",
        "RR Case",
        "LR Case",
        "RL Case"
    };

    for (int i = 0; i < 4; i++) {

        Node* root = nullptr;

        cout << "\n====================\n";
        cout << cases[i] << endl;

        for (int j = 0; j < 3; j++) {
            root = insertAVL(root, sequences[i][j]);
        }

        cout << "Preorder: ";
        preorder(root);

        cout << "\nInorder: ";
        inorder(root);

        cout << "\n\nBalance Verification:\n";
        displayBalance(root);

        destroyTree(root);
    }

    return 0;
}
