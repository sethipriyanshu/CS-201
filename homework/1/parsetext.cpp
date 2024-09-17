#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <unordered_map>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    vector<string> tokens;
    unordered_map<string, int> wordCount;
    const regex delim("\\s+");

    auto begin = sregex_token_iterator(text.begin(), text.end(), delim, -1);
    auto end = sregex_token_iterator();
    for (sregex_token_iterator word = begin; word != end; word++) {
        string token = *word;
        tokens.push_back(token);
        wordCount[token]++;
    }

    for (const auto& pair : wordCount) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}