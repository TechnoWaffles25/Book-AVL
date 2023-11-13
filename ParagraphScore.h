#ifndef PARAGRAPH_SCORE_H
#define PARAGRAPH_SCORE_H

#include <vector>
#include "token.h"

struct ParagraphScore {
    int paragraphIndex;
    double score;
    std::vector<const TokenInfo*> tokenInfos; // Almacena punteros a TokenInfo

    ParagraphScore(int index) : paragraphIndex(index), score(0.0) {}

    void addTokenInfo(const TokenInfo* tokenInfo) {
        tokenInfos.push_back(tokenInfo);
    }

    void calculateScore(const std::vector<std::string>& searchTokens) {
        if (tokenInfos.empty()) {
            return; // No hay tokens para calcular la puntuación
        }

        int orderMatchCount = 0;
        int lastWordIndex = -1;
        int totalDistance = 0;

        for (const auto& searchToken : searchTokens) {
            for (const auto& tokenInfo : tokenInfos) {
                if (tokenInfo->token == searchToken) {
                    for (const auto& position : tokenInfo->positions) {
                        if (position.paragraphIndex == paragraphIndex) {
                            if (lastWordIndex != -1) {
                                totalDistance += abs(position.wordIndex - lastWordIndex);
                            }
                            lastWordIndex = position.wordIndex;
                            orderMatchCount++;
                            break;
                        }
                    }
                    break;
                }
            }
        }

        if (orderMatchCount == searchTokens.size()) {
            // Todas las palabras están en el orden correcto
            score = 100.0 / (1 + totalDistance); // Ejemplo de cálculo de puntuación
        } else {
            score = 0.0; // No todas las palabras están en el orden correcto
        }
    }
};
#endif