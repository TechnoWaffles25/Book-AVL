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

using namespace std;

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

    vector<string> tokenize(const string& text) const {
        vector<string> tokens;
        istringstream iss(text);
        string token;
        while (iss >> token) {
            token = removePunctuation(token);
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
};

#endif