#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>
#include <vector>
#include <chrono>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <db file> <query file>" << std::endl;
        return -1;
    }

    std::unordered_map<std::string, std::vector<std::string>> movieToActors;
    std::unordered_map<std::string, std::vector<std::string>> actorToMovies;
    std::string line, movie;
    std::regex delim("/");

    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream dbfile(argv[1]);
    if (!dbfile.is_open()) {
        std::cout << "Unable to open file: " << argv[1] << std::endl;
        return -1;
    }

    int recordCount = 0;
    while (std::getline(dbfile, line)) {
        auto begin = std::sregex_token_iterator(line.begin(), line.end(), delim, -1);
        auto end = std::sregex_token_iterator();
        if (begin == end) continue;

        movie = *begin++;
        std::vector<std::string> actors;
        for (auto it = begin; it != end; ++it) {
            std::string actor = *it;
            actors.push_back(actor);
            actorToMovies[actor].push_back(movie);
        }
        movieToActors[movie] = actors;
        recordCount++;
    }
    dbfile.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> creationTime = end - start;

    start = std::chrono::high_resolution_clock::now();

    std::ifstream queryfile(argv[2]);
    if (!queryfile.is_open()) {
        std::cout << "Unable to open file: " << argv[2] << std::endl;
        return -1;
    }

    while (std::getline(queryfile, line)) {
        if (movieToActors.find(line) != movieToActors.end()) {
            std::cout << "Actors in movie \"" << line << "\":" << std::endl;
            for (const auto& actor : movieToActors[line]) {
                std::cout << "\t" << actor << std::endl;
            }
        } else if (actorToMovies.find(line) != actorToMovies.end()) {
            std::cout << "Movies with actor \"" << line << "\":" << std::endl;
            for (const auto& movie : actorToMovies[line]) {
                std::cout << "\t" << movie << std::endl;
            }
        } else {
            std::cout << "Not Found: " << line << std::endl;
        }
    }
    queryfile.close();

    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> searchTime = end - start;

    std::chrono::duration<double> totalTime = creationTime + searchTime;

    std::cout << "\n# of records: " << recordCount << std::endl;
    std::cout << "Time taken to create data structure: " << creationTime.count() << " seconds" << std::endl;
    std::cout << "Time taken to search: " << searchTime.count() << " seconds" << std::endl;
    std::cout << "Total time taken: " << totalTime.count() << " seconds" << std::endl;

    return 0;
}