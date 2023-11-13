#include <iostream>
#include "B+Tree.h"
#include <vector>
#include "processTxt.h"
#include <unordered_set>
#include <map>
#include "ParagraphScore.h"
#include <string>
#include <algorithm>

int main() {
    // Esto deberia venir del preliminar 1, todas las rutas de los archivos a procesar
    std::vector<std::string> files;
    files.push_back("Books/AliceInWonderland.txt");

    // Crear un arbol B+ con un orden de 50
    BPlusTree<TokenInfo> bpt(50);
    TextProcessing tp;

    // Cargamos Stop Words
    std::unordered_set<std::string> stopWords = {/* Stop Words*/};
    tp.setStopWords(stopWords);

    // Loop through the files
    for (const auto& file : files) {
        auto paragraphs = tp.tokenizeFileByParagraphs(file);
        for (const auto& paragraphPair : paragraphs) {
            for (const auto& tokenInfo : paragraphPair.second) {
                bpt.insert(tokenInfo); // Insert the entire TokenInfo object into the B+ tree
            }
        }
    }

    // Ejemplo para buscar una frase usando el árbol B+
    std::string phraseToSearch = "fighting for hedgehogs";
    std::vector<std::string> tokens = tp.tokenize(phraseToSearch, true); // Tokenizamos la frase de igual manera que el parrafo
    std::vector <TokenInfo*> foundTokenInfos; // Vector de punteros a TokenInfo
    bool allTokensFound = true;

    for (const auto& token : tokens) {
        std::cout << "Buscando el token: " << token << std::endl;
        foundTokenInfos = bpt.searchAll(TokenInfo{token, {}});

        if (!foundTokenInfos.empty()) {
            std::cout << "El token '" << token << "' fue encontrado." << std::endl;
            for (const auto& tokenInfo : foundTokenInfos) {
                for (const auto& position : tokenInfo->positions) {
                    std::cout << " - Encontrado en el parrafo " << position.paragraphIndex 
                              << ", palabra " << position.wordIndex << std::endl;
                }
            }
        } else {
            allTokensFound = false;
            std::cout << "El token '" << token << "' no fue encontrado." << std::endl;
        }
    }

    if (allTokensFound) {
        std::cout << "Todos los tokens de la frase fueron encontrados en el arbol B+." << std::endl;
    } else {
        std::cout << "No todos los tokens de la frase fueron encontrados en el arbol B+." << std::endl;
    }

    // Logica de puntuacion de parrafos
    std::map<int, ParagraphScore> paragraphScores;
    for (TokenInfo* tokenInfo : foundTokenInfos) {
        for (const auto& position : tokenInfo->positions) {
            // Verificar si el ParagraphScore ya existe para este índice de párrafo
            auto it = paragraphScores.find(position.paragraphIndex);
            if (it == paragraphScores.end()) {
                // Si no existe, crea uno nuevo y obtén un iterador a él
                it = paragraphScores.insert({position.paragraphIndex, ParagraphScore(position.paragraphIndex)}).first;
            }

            // Ahora agrega el TokenInfo al ParagraphScore correspondiente
            it->second.addTokenInfo(tokenInfo);
        }
    }

    // Calcular puntuaciones para cada párrafo
    for (auto& pair : paragraphScores) {
        ParagraphScore& score = pair.second;
        score.calculateScore(tokens);
    }

    // Transferir a un vector para ordenar
    std::vector<ParagraphScore> sortedScores;
    for (const auto& pair : paragraphScores) {
        sortedScores.push_back(pair.second);
    }

    // Ordenar el vector
    std::sort(sortedScores.begin(), sortedScores.end(), 
        [](const ParagraphScore& a, const ParagraphScore& b) {
            return a.score > b.score; // Orden descendente por score
        });

    // Imprimir los resultados
    for (const auto& score : sortedScores) {
        std::cout << "Parrafo " << score.paragraphIndex << " - Puntuación: " << score.score << std::endl;
    }
}
