#41343146
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

Node* Insert(Node* root, int key) {
    if (!root) return new Node(key);
    if (key < root->key) root->left = Insert(root->left, key);
    else root->right = Insert(root->right, key);
    return root;
}

int Height(Node* root) {
    if (!root) return 0;
    return 1 + max(Height(root->left), Height(root->right));
}

Node* FindMin(Node* root) {
    while (root->left) root = root->left;
    return root;
}

Node* Delete(Node* root, int key) {
    if (!root) return nullptr;
    if (key < root->key) root->left = Delete(root->left, key);
    else if (key > root->key) root->right = Delete(root->right, key);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        } else {
            Node* temp = FindMin(root->right);
            root->key = temp->key;
            root->right = Delete(root->right, temp->key);
        }
    }
    return root;
}

int main() {
    srand(time(0));
    int ns[] = {100, 500, 1000, 2000, 3000, 10000};
    for (int n : ns) {
        Node* root = nullptr;
        for (int i = 0; i < n; i++) {
            int val = rand();
            root = Insert(root, val);
        }
        int h = Height(root);
        double ratio = (double)h / log2(n);
        cout << "n=" << n << " Height=" << h << " Ratio=" << ratio << endl;
    }
 
    Node* root = nullptr;
    root = Insert(root, 50);
    root = Insert(root, 30);
    root = Insert(root, 70);
    root = Insert(root, 20);
    root = Insert(root, 40);
    root = Insert(root, 60);
    root = Insert(root, 80);

    cout << "BST Height before delete: " << Height(root) << endl;
    root = Delete(root, 30);
    cout << "BST Height after delete: " << Height(root) << endl;

    return 0;
}