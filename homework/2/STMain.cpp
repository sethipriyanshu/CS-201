#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <vector>
#include "ST.hpp"
#include <regex>

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

    // Check if file argument is provided
    if (argc < 2) {
        std::cerr << "Error: Provide the input file as a command line argument." << std::endl;
        return 1;
    }

    // Open the file provided in the argument
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << argv[1] << std::endl;
        return 1;
    }

    // Start timing the execution
    auto startTime = std::chrono::high_resolution_clock::now();

    // Initialize string and search tree for word frequency count
    string word;
    ST<string, int> wordCounter;
    const std::regex pattern("\\s+");

    // Read and process words from the file
    while (inputFile >> word) {
        std::sregex_token_iterator token(word.begin(), word.end(), pattern, -1);
        std::sregex_token_iterator end;

        for (; token != end; ++token) {
            if (!token->str().empty()) {
                wordCounter[*token]++;  // Increment frequency count for each word
            }
        }
    }

    // End timing and calculate duration
    auto endTime = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    inputFile.close();

    // Display word frequencies in a tabular format
    cout << "Word Count (Tabular Format):" << endl;
    wordCounter.display();

    // Convert the tree to a vector and display it
    cout << "\nTree Vector (Key-Value Pairs):" << endl;
    std::vector<std::pair<string, int>> treeVector = wordCounter.toVector();
    for (const auto& kv : treeVector) {
        cout << kv.first << ": " << kv.second << endl;
    }

    cout << "\nNumber of unique words: " << wordCounter.size() << endl;
    cout << "Execution time: " << elapsed.count() << " milliseconds" << endl;

    return 0;
}
