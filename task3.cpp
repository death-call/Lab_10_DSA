
#include <iostream>
#include <string>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
};

int getHeight(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    return root->height;
}

int getBalance(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    return getHeight(root->left) - getHeight(root->right);
}

Node* createNode(int value) {
    Node* newNode = new Node;

    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;

    return newNode;
}


Node* rightRotate(Node* root) {

    Node* newRoot = root->left;
    Node* temp = newRoot->right;

    newRoot->right = root;
    root->left = temp;

    // Update old root first
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

Node* leftRotate(Node* root) {

    Node* newRoot = root->right;
    Node* temp = newRoot->left;

    newRoot->left = root;
    root->right = temp;

    // Update old root first
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

Node* insertAVL(Node* root, int value) {

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

    // Update height
    root->height = 1 + max(
        getHeight(root->left),
        getHeight(root->right)
    );

    int balance = getBalance(root);

    // LL
    if (balance > 1 && value < root->left->data) {
        return rightRotate(root);
    }

    // RR
    if (balance < -1 && value > root->right->data) {
        return leftRotate(root);
    }

    // LR
    if (balance > 1 && value > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL
    if (balance < -1 && value < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node* findMin(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }

    return root;
}
 //TASK 3 ADDITION 
Node* deleteAVL(Node* root, int value) {

    if (root == nullptr) {
        return nullptr;
    }

    if (value < root->data) {
        root->left = deleteAVL(root->left, value);
    }
    else if (value > root->data) {
        root->right = deleteAVL(root->right, value);
    }
    else {

        // Case 1: Leaf node
        if (root->left == nullptr &&
            root->right == nullptr) {

            delete root;
            return nullptr;
        }

        // Case 2: One child
        else if (root->left == nullptr ||
            root->right == nullptr) {

            Node* temp;

            if (root->left != nullptr) {
                temp = root->left;
            }
            else {
                temp = root->right;
            }

            delete root;
            root = temp;
        }

        // Case 3: Two children
        else {

            Node* temp = findMin(root->right);

            root->data = temp->data;

            root->right = deleteAVL(
                root->right, temp->data
            );
        }
    }

    if (root == nullptr) {
        return nullptr;
    }

    root->height = 1 + max(
        getHeight(root->left),
        getHeight(root->right)
    );

    int balance = getBalance(root);


    // Left heavy
    if (balance > 1) {

        // LL or child balance factor 0
        if (getBalance(root->left) >= 0) {
            return rightRotate(root);
        }

        // LR
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }

    // Right heavy
    if (balance < -1) {

        // RR or child balance factor 0
        if (getBalance(root->right) <= 0) {
            return leftRotate(root);
        }

        // RL
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

void preorder(Node* root) {
    if (root == nullptr) {
        return;
    }

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root) {
    if (root == nullptr) {
        return;
    }

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void displayBalance(Node* root) {
    if (root == nullptr) {
        return;
    }

    cout << "Node: " << root->data
        << " | Height: " << root->height
        << " | Balance Factor: " << getBalance(root)
        << endl;

    displayBalance(root->left);
    displayBalance(root->right);
}

void destroyTree(Node* root) {
    if (root == nullptr) {
        return;
    }

    destroyTree(root->left);
    destroyTree(root->right);

    delete root;
}

void displayTree(Node* root) {

    cout << "\nPreorder: ";
    preorder(root);

    cout << "\nInorder: ";
    inorder(root);

    cout << "\n\nNode Information:\n";
    displayBalance(root);

    cout << endl;
}

int task3() {

    Node* root = nullptr;

    int values[] = { 30, 20, 40, 10, 25, 50, 5 };

    // Insert values
    for (int i = 0; i < 7; i++) {
        root = insertAVL(root, values[i]);
    }

    cout << "Original AVL Tree:";
    displayTree(root);

    // Delete 50
    root = deleteAVL(root, 50);

    cout << "\nAfter deleting 50:";
    displayTree(root);

    // Delete 40
    root = deleteAVL(root, 40);

    cout << "\nAfter deleting 40:";
    displayTree(root);

    // Test missing key
    root = deleteAVL(root, 100);

    cout << "\nAfter deleting missing key 100:";
    displayTree(root);

    destroyTree(root);

    // Test empty tree
    Node* empty = nullptr;

    empty = deleteAVL(empty, 10);

    cout << "\nEmpty tree deletion: "
        << (empty == nullptr ? "nullptr" : "Not empty")
        << endl;

    // Test single-node tree
    Node* single = createNode(10);

    single = deleteAVL(single, 10);

    cout << "Single-node deletion: "
        << (single == nullptr ? "nullptr" : "Not empty")
        << endl;

    // Test heavy child balance factor 0
    Node* test = nullptr;

    int testValues[] = { 4, 2, 6, 5, 7 };

    for (int i = 0; i < 5; i++) {
        test = insertAVL(test, testValues[i]);
    }

    cout << "\nHeavy child BF = 0 test:";
    test = deleteAVL(test, 2);

    displayTree(test);

    destroyTree(test);

    return 0;
}
