#ifndef STRUCTBOOK_H
#define STRUCTBOOK_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

struct Book {
    string author;
    string title;
    string genre;
    string key;
    string path;

    Book(const string& author, const string& title, const string& genre) {
        this->author = author;
        this->title = title;
        this->genre = genre;
        this->key = author + "-" + title + "-" + genre;
    }
    Book(const string& path){
        this->path = path;
        ifstream file(path);

        if (file.is_open()){
            getline(file, this->title);
            getline(file, this->author);
            getline(file, this->genre);
            this->key = author + "-" + title + "-" + genre;
            file.close();
        } else {
            cerr << "Error al abrir el archivo del libro: " << path << endl;
        }
    }

    string getAuthor() {
        return this->author;
    }
    string getTitle() {
        return this->title;
    }
    string getGenre() {
        return this->genre;
    }
    string getKey() {
        return this->key;
    }
    string toString() const {
        return "Title: " + title + ", Author: " + author + ", Genre: " + genre;
    }
};
#endif