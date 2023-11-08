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
    //files.push_back("Books/ATaleOfTwoCities.txt");

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

    // Example for searching a single word using the B+ tree
    std::string wordToSearch = "heads"; // Example word, after processing the phrase

    // Process the word to fit the format stored in the B+ tree
    TokenInfo searchKey;
    searchKey.token = wordToSearch;
    if(bpt.search(searchKey)) {
        std::cout << "The word '" << wordToSearch << "' was found!" << std::endl;
    } else {
        std::cout << "The word '" << wordToSearch << "' was not found." << std::endl;
    }
    /*std::string phrase = "Off with their heads!";
    auto phraseTokens = tp.processText(phrase);
    for (string token : phraseTokens) {
        cout << "Phrase tokens: " << token << endl;
    }

    // Create a map to store the TF-IDF score for each file
    std::map<std::string, double> fileScores;

    // Calculate the TF-IDF score for each file
    for (const auto& file : files) {
        auto tokens = tp.tokenizeFileFromLine4(file);
        cout << "Tokens: " << tokens.size() << endl;
        double score = 0.0;
        for (const auto& token : phraseTokens) {
            // Calculate the TF-IDF score for the token
            double tf = std::count(tokens.begin(), tokens.end(), token);
            double idf = std::log(static_cast<double>(files.size()) / (bpt.search(token) ? 1.0 : 0.0));
            score += tf * idf;
        }
        fileScores[file] = score;
    }

    // Sort the files by their TF-IDF scores in descending order
    std::vector<std::pair<std::string, double>> sortedFiles(fileScores.begin(), fileScores.end());
    std::sort(sortedFiles.begin(), sortedFiles.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // Print the ranked files
    for (const auto& file : sortedFiles) {
        std::cout << "File: " << file.first << ", Score: " << file.second << std::endl;
    }*/
}