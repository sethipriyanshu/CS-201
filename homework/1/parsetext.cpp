#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
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

    std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::vector<std::string> tokens;
    const std::regex delim("\\s+");

    auto begin = std::sregex_token_iterator(text.begin(), text.end(), delim, -1);
    auto end = std::sregex_token_iterator();
    for (std::sregex_token_iterator word = begin; word != end; word++) {
        tokens.push_back(*word);
    }

    for (const auto& str : tokens)
        std::cout << str << std::endl;

    return 0;
}