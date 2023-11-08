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

    std::vector<std::string> files;
    files.push_back("Books/AliceInWonderland.txt");
    //files.push_back("Books/ATaleOfTwoCities.txt");
    BPlusTree<std::string> bpt(50);

    TextProcessing tp;
    std::unordered_set<std::string> stopWords = {
        "the", "a", "an", "and", "or", "but", "is", "are", "was", "were", 
        "of", "at", "for", "with", "in", "on", "to"
    };

    tp.setStopWords(stopWords);
    for(const auto& file : files){
        auto tokens = tp.tokenizeFileFromLine4(file);
        for(const auto& token : tokens){
            bpt.insert(token);
        }
    }

    std::cout<<std::endl;
    bpt.bpt_print();

    std::string phrase = "Off with their heads!";
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
    }
//    std::cout<<std::endl<<std::endl;


//    int* result_array = new int[8];
//    int result = bpt.range_search(150, 240, result_array, 8);
//
//    std::cout << result << '\n'; // 8
//
//    for (int i = 0; i < result; i++) {
//        std::cout << result_array[i] << ' ';
//    }
//    std::cout << '\n'; // 5, 6, 10*/

 /*  bpt.remove(152);
    bpt.remove(269);
    bpt.remove(256);


    std::cout<<"ㄴㄴㄴ"<<std::endl;
    bpt.remove(467);
    bpt.bpt_print();

//    bpt.remove(217);

//
//    std::cout<<std::endl;
//    bpt.bpt_print();
    std::cout<<std::endl<<std::endl;
    bpt.remove(764);
    bpt.remove(863);

    std::cout<<std::endl;
//    bpt.getroot();
    bpt.bpt_print();

    bpt.remove(71);
    bpt.remove(100);
    bpt.remove(139);

    std::cout<<std::endl;
    bpt.bpt_print();

    bpt.remove(368);


    std::cout<<std::endl;
    bpt.bpt_print();


*/

//
//
//
//
//    BPlusTree<int> bpt(3);
//    bpt.insert(1);
//    bpt.insert(2);
//    bpt.insert(3);
//    bpt.insert(4);
//    bpt.insert(5);
//
//    print_bool(bpt.search(2)); // True
//    print_bool(bpt.search(42)); // False
//
//
//    bpt.remove(3);
//
//    bpt.bpt_print();
//
//    print_bool(bpt.search(3)); // False
//
//    bpt.insert(6);
//    bpt.insert(10);
//    std::cout << '\n';
//    bpt.bpt_print();
//
//    std::cout << '\n';
//
//    int* result_array = new int[3];
//    int result = bpt.range_search(3, 7, result_array, 3);
//
//    std::cout << result << '\n'; // 3
//    for (int i = 0; i < result; i++) {
//        std::cout << result_array[i] << ' ';
//    }
//    std::cout << '\n'; // 5, 6, 10
}