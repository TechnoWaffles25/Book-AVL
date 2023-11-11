#include <iostream>
#include "B+Tree.h"
#include <vector>
#include "processTxt.h"
#include <map>

void print_bool(bool cond) {
    if (cond) {
        std::cout << "True\n";
    } else {
        std::cout << "False\n";
    }
}

int main() {

    // Esto deberia venir del preliminar 1 
    std::vector<std::string> files;
    files.push_back("Books/AliceInWonderland.txt");

    BPlusTree<TokenInfo> bpt(50); // Assuming your B+ Tree is now templated to handle TokenInfo objects
    TextProcessing tp;

    // Load stop words (provided by ChatGPT or loaded from a file)
    std::unordered_set<std::string> stopWords = {
        //... Your stop words
    };
    tp.setStopWords(stopWords);

    // Loop through the files
    int fileIndex = 0;
    for (const auto& file : files) {
        auto paragraphs = tp.tokenizeFileByParagraphs(file);
        for (const auto& paragraphPair : paragraphs) {
            int paragraphIndex = paragraphPair.first;
            for (const auto& tokenInfo : paragraphPair.second) {
                // Now, we have tokenInfo which contains the token and its positions
                bpt.insert(tokenInfo); // We insert the entire TokenInfo object into the B+ tree
            }
        }
        fileIndex++; // Increment file index for next file
    }

    std::cout<<std::endl;
    //bpt.bpt_print();

    // Ejemplo para buscar una frase usando el árbol B+
    std::string phraseToSearch = "off with their heads!"; // Ejemplo de frase

    // Procesar la frase para ajustarla al formato almacenado en el árbol B+
    std::vector<std::string> tokens = tp.tokenize(phraseToSearch); // Asumiendo que tienes un método para tokenizar frases

    bool allTokensFound = true;
    for (const auto& token : tokens) {
        std::cout << "Searching for token: " << token << std::endl;
        TokenInfo searchKey;
        searchKey.token = token;
        if (!bpt.search(searchKey)) {
            allTokensFound = false;
            std::cout << "El token '" << token << "' no fue encontrado." << std::endl;
        }
    }

    if (allTokensFound) {
        std::cout << "Todos los tokens de la frase fueron encontrados en el arbol B+." << std::endl;
    } else {
        std::cout << "No todos los tokens de la frase fueron encontrados en el arbol B+." << std::endl;
    }
}