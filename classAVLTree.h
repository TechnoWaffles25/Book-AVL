#ifndef CLASSAVLTREE_H
#define CLASSAVLTREE_H

#include "structNode.h"
#include <string>

using namespace std;

class AVLTree {
private:
    Node* root;

    // Helper function to calculate the height of a node
    int height(Node* node) {
        return node ? node->height : 0;
    }

    // Helper function to update the height of a node
    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + max(height(node->left), height(node->right));
        }
    }

    // Helper function to perform a right rotation
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Helper function to perform a left rotation
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Helper function to balance the AVL tree
    Node* balance(Node* node) {
        int balanceFactor = height(node->left) - height(node->right);

        // Left Heavy
        if (balanceFactor > 1) {
            if (node->left && keyCompare(node->left->book.key, node->book.key) > 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        // Right Heavy
        if (balanceFactor < -1) {
            if (node->right && keyCompare(node->right->book.key, node->book.key) < 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    // Compare two keys (e.g., lexicographically)
    // C++ tiene una funcion para comparar strings lexicograficamente, lo usamos para comparar e indexar las llaves de los libros
    int keyCompare(const string& key1, const string& key2) {
        return key1.compare(key2);
    }

    int countNodes(Node* node) {
        if (!node) {
            return 0;
        }
        return 1 + countNodes(node->left) + countNodes(node->right);
    }
    
public:
    AVLTree() : root(nullptr) {}

    // Insert a book into the AVL tree
    Node* insert(Node* node, Book book) {
        if (!node) {
            return new Node(book);
        }

        if (keyCompare(book.key, node->book.key) < 0) {
            node->left = insert(node->left, book);
        } else {
            node->right = insert(node->right, book);
        }

        updateHeight(node);
        return balance(node);
    }

    // Public insert method
    void insert(Book book) {
        root = insert(root, book);
    }

    // Search for a book by key
    void fullTextSearch(Node* node, const string& key, vector<Node*>& results) {
        if (!node) {
            return;
        }

        if (node->book.author.find(key) != string::npos ||
            node->book.title.find(key) != string::npos ||
            node->book.genre.find(key) != string::npos) {
            results.push_back(node);
        }

        fullTextSearch(node->left, key, results);
        fullTextSearch(node->right, key, results);
    }

    // Public search method
    vector<Node*> fullTextSearch(const string& key) {
        vector<Node*> results;
        fullTextSearch(root, key, results);
        return results;
    }

    int countNodes() {
        return countNodes(root);
    }
};
#endif 