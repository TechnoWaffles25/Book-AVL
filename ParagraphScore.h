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
            return; // No tokens to calculate score for
        }

        int matchCount = 0;
        int lastWordIndex = -1;
        int totalDistance = 0;

        for (const auto& searchToken : searchTokens) {
            bool tokenFound = false;
            for (const auto& tokenInfo : tokenInfos) {
                if (tokenInfo->token == searchToken) {
                    for (const auto& position : tokenInfo->positions) {
                        if (position.paragraphIndex == paragraphIndex) {
                            if (lastWordIndex != -1) {
                                totalDistance += abs(position.wordIndex - lastWordIndex);
                            }
                            lastWordIndex = position.wordIndex;
                            matchCount++;
                            tokenFound = true;
                            break;
                        }
                    }
                    if (tokenFound) {
                        break;
                    }
                }
            }
        }

        if (matchCount > 0) {
            // Give a score based on the number of matches and the total distance between them
            score = (double)matchCount / searchTokens.size() * 100.0 / (1 + totalDistance);
        } else {
            score = 0.0; // No matches found
        }
    }


};
#endif