#include "classAVLTree.h"
#include "structNode.h"
#include "structBook.h"
#include <iostream>

using namespace std;

int main() {
    // Create an AVLTree
    AVLTree avl;

    // Create some books
    Book book1("Books/AliceInWonderland.txt");
    Book book2("J.K. Rowling", "Harry Potter and the Philosopher's Stone", "Fantasy");
    Book book3("J.R.R. Tolkien", "The Lord of the Rings", "Fantasy");
    Book book4("Harper Lee", "To Kill a Mockingbird", "Southern Gothic");
    Book book5("F. Scott Fitzgerald", "The Great Gatsby", "Tragedy");
    Book book6("Jane Austen", "Pride and Prejudice", "Romance");
    Book book7("Mark Twain", "Adventures of Huckleberry Finn", "Picaresque");
    Book book8("Ernest Hemingway", "The Old Man and the Sea", "Adventure");
    Book book9("John Steinbeck", "Of Mice and Men", "Tragedy");
    Book book10("Arthur Conan Doyle", "The Adventures of Sherlock Holmes", "Mystery");
    Book book11("J.K. Rowling", "Harry Potter and the Chamber of Secrets", "Fantasy");
    Book book12("J.K. Rowling", "Harry Potter and the Prisoner of Azkaban", "Fantasy");
    Book book13("J.K. Rowling", "Harry Potter and the Goblet of Fire", "Fantasy");
    Book book14("J.K. Rowling", "Harry Potter and the Order of the Phoenix", "Fantasy");
    Book book15("J.K. Rowling", "Harry Potter and the Half-Blood Prince", "Fantasy");
    Book book16("J.K. Rowling", "Harry Potter and the Deathly Hallows", "Fantasy");

    // Insert the books into the AVLTree
    avl.insert(book1);
    avl.insert(book2);
    avl.insert(book3);
    avl.insert(book4);
    avl.insert(book5);
    avl.insert(book6);
    avl.insert(book7);
    avl.insert(book8);
    avl.insert(book9);
    avl.insert(book10);
    avl.insert(book11);
    avl.insert(book12);
    avl.insert(book13);
    avl.insert(book14);
    avl.insert(book15);
    avl.insert(book16);

    // Search for a book
    vector<Node*> result = avl.fullTextSearch("Ha");

    // If the book is found, print its title
    if (!result.empty()) {
        for (Node* node : result) {
            cout << "Found: " << node->book.getTitle() << endl;
        }
    } else {
        cout << "Book not found" << endl;
    }
    cout << "Number of nodes: " << avl.countNodes() << endl;

    return 0;
}