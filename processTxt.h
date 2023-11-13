#ifndef PROCESSBOOK_H
#define PROCESSBOOK_H

#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <stdexcept>
#include <iostream>

#include "token.h"

using namespace std;


// Overload the << operator to handle TokenPosition objects
std::ostream& operator<<(std::ostream& os, const TokenPosition& position) {
    os << "Paragraph: " << position.paragraphIndex << ", Word: " << position.wordIndex;
    return os;
}

// Overload the << operator to handle TokenInfo objects
std::ostream& operator<<(std::ostream& os, const TokenInfo& info) {
    // Output the token
    os << info.token;

    // Optionally, output the positions vector
    if (!info.positions.empty()) {
        os << " [";
        for (size_t i = 0; i < info.positions.size(); ++i) {
            if (i > 0) {
                os << ", ";
            }
            os << info.positions[i];
        }
        os << "]";
    }

    // Return the ostream to allow chaining
    return os;
}

bool operator==(const TokenPosition& lhs, const TokenPosition& rhs) {
    return lhs.paragraphIndex == rhs.paragraphIndex && lhs.wordIndex == rhs.wordIndex;
}

bool operator<(const TokenPosition& lhs, const TokenPosition& rhs) {
    if (lhs.paragraphIndex == rhs.paragraphIndex) {
        return lhs.wordIndex < rhs.wordIndex;
    }
    return lhs.paragraphIndex < rhs.paragraphIndex;
}

class TextProcessing {
private:
    unordered_set<string> stopWords;

public:
    unordered_set<string> getStopWords() const {
        return stopWords;
    }
    void setStopWords(const unordered_set<string>& stopWords) {
        this->stopWords = stopWords;
    }
    
    void loadStopWords(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Unable to open stop words file.");
        }

        string word;
        while (file >> word) {
            stopWords.insert(word);
        }
        file.close();
    }

    vector<string> tokenize(const string& text, bool keepPunctuation = false) const {
        vector<string> tokens;
        istringstream iss(text);
        string token;
        while (iss >> token) {
            if (!keepPunctuation) {
                token = removePunctuation(token);
            }
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }
        return tokens;
    }

    string toLower(const string& str) const {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                       [](unsigned char c) { return tolower(c); });
        return lowerStr;
    }

    string removePunctuation(const string& token) const {
        string newToken;
        remove_copy_if(token.begin(), token.end(), back_inserter(newToken),
                            [](char c) { return ispunct(c); });
        return newToken;
    }

    vector<string> removeStopWords(const vector<string>& tokens) const {
        vector<string> filteredTokens;
        for (const auto& token : tokens) {
            if (stopWords.find(token) == stopWords.end()) {
                filteredTokens.push_back(token);
            }
        }
        return filteredTokens;
    }

    vector<string> processText(const string& text) const {
        string lowerText = toLower(text);
        auto tokens = tokenize(lowerText);
        return removeStopWords(tokens);
    }

    vector<string> tokenizeFileFromLine4(const string& filepath) const {
        ifstream file(filepath);
        if (!file.is_open()) {
            throw runtime_error("Unable to open file: " + filepath);
        }

        // Skip the first three lines
        string line;
        for (int i = 0; i < 3; ++i) {
            if (!getline(file, line)) {
                throw runtime_error("File does not have enough lines.");
            }
        }

        // Read and tokenize the rest of the file
        vector<string> allTokens;
        while (getline(file, line)) {
            vector<string> tokens = processText(line); // processText already converts to lower case and removes stop words
            allTokens.insert(allTokens.end(), tokens.begin(), tokens.end());
        }

        file.close();
        return allTokens; // No need to remove stop words again
    }

    // Función modificada para procesar el archivo por párrafos y registrar la posición de los tokens
    vector<pair<int, vector<TokenInfo>>> tokenizeFileByParagraphs(const string& filepath) const {
        ifstream file(filepath);
        if (!file.is_open()) {
            throw runtime_error("Unable to open file: " + filepath);
        }

        // Skip the first three lines
        string line;
        for (int i = 0; i < 3; ++i) {
            getline(file, line); // You should handle potential errors here as well
        }

        vector<pair<int, vector<TokenInfo>>> paragraphs;
        unordered_map<string, TokenInfo> paragraphTokens;
        string paragraph;
        int paragraphIndex = 0;

        while (getline(file, line)) {
            if (line.empty()) { // Empty lines delimit paragraphs
                if (!paragraph.empty()) {
                    vector<TokenInfo> tokensInfo;
                    // Tokenize the paragraph with punctuation
                    vector<string> tokens = tokenize(paragraph, true); 
                    int wordIndex = 0;
                    for (const auto& token : tokens) {
                        TokenPosition position = {paragraphIndex, wordIndex++};
                        // If the token is new to this paragraph, initialize TokenInfo
                        if (paragraphTokens.find(token) == paragraphTokens.end()) {
                            paragraphTokens[token] = TokenInfo{token};
                        }
                        // Add the position of the token to the paragraph's TokenInfo
                        paragraphTokens[token].positions.push_back(position);
                    }
                    // Move the TokenInfo for each token into the tokensInfo vector
                    for (auto& pair : paragraphTokens) {
                        tokensInfo.push_back(std::move(pair.second));
                    }
                    paragraphs.push_back({paragraphIndex++, tokensInfo});
                    paragraph.clear();
                    paragraphTokens.clear(); // Clear the tokens for the new paragraph
                }
            } else {
                paragraph += line + " ";
            }
        }

        // Handle the last paragraph if the file doesn't end with a newline
        if (!paragraph.empty()) {
            vector<TokenInfo> tokensInfo;
            vector<string> tokens = tokenize(paragraph, true); // Tokenize with punctuation
            int wordIndex = 0;
            for (const auto& token : tokens) {
                TokenPosition position = {paragraphIndex, wordIndex++};
                if (paragraphTokens.find(token) == paragraphTokens.end()) {
                    paragraphTokens[token] = TokenInfo{token};
                }
                paragraphTokens[token].positions.push_back(position);
            }
            for (auto& pair : paragraphTokens) {
                tokensInfo.push_back(std::move(pair.second));
            }
            paragraphs.push_back({paragraphIndex, tokensInfo});
        }

        file.close();
        return paragraphs;
    }

};

#endif