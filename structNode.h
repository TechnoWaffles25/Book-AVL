#ifndef STRUCTNODE_H
#define STRUCTNODE_H

#include "structBook.h"

struct Node {
    Book book;
    Node* left;
    Node* right;
    int height;

    Node(Book book): book(book) {
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }
};
#endif