/*
  Author: Psethi
  Email: psethi@crimson.ua.edu
  Section: Fall 2024 CS 201
  Assignment: 2
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "ST.hpp"
#include <cctype>
#include <chrono>


// remove puncutation and lowercase
std::string cleanWord(const std::string& word) {
    std::string res;
    res.reserve(word.length());
    for (size_t i = 0; i < word.length(); ++i) {
        if (std::isalpha(word[i])) {
            res += std::tolower(word[i]);
        }
    }
    return res;
}


// print function
void printWordFrequency(const std::string& word, int frequency, int maxWordLength) {
    std::cout << std::left << std::setw(maxWordLength + 2) << word 
              << std::right << std::setw(5) << frequency << std::endl;
}

int main(int argc, char* argv[]) {
    // Check cinput
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    // Open input file
    std::ifstream inFile(argv[1]);
    if (!inFile) {
        std::cerr << "Unable to open file" << argv[1] << "'" << std::endl;
        return 1;
    }

    // clock
    auto start = std::chrono::high_resolution_clock::now();

    // count frequencies
    ST<std::string, int> wordFreq;
    std::string word;
    size_t maxWordLength = 0;

    // Read and process words
    while (inFile >> word) {
        std::string cleaned = cleanWord(word);
        if (!cleaned.empty()) {
            wordFreq[cleaned]++;
            maxWordLength = std::max(maxWordLength, cleaned.length());
        }
    }

    // clock end
    

    auto wordFreqVector = wordFreq.toVector();
    
    // Sorting
    std::sort(wordFreqVector.begin(), wordFreqVector.end(),
        [](const auto& a, const auto& b) {
            return (a.second > b.second) || 
                   (a.second == b.second && a.first < b.first);
        });
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    
    // Display words
    size_t displayCount = std::min(size_t(10), wordFreqVector.size());
    for (size_t i = 0; i < displayCount; ++i) {
        printWordFrequency(wordFreqVector[i].first, 
                          wordFreqVector[i].second, 
                          maxWordLength);
    }
    // output
    std::cout << "number of words: " << wordFreq.size() << std::endl;
    std::cout << "time taken: " << duration.count() << " seconds\n" << std::endl;

    return 0;
}