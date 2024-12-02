/*
  Author: Priyanshu Sethi
  Email: psethi@crimson.ua.edu
  Section: Fall 2024 CS 201
  Assignment: 3
*/

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>
#include <vector>
#include <chrono>

int main(int argc, char *argv[]) {
    // Check for correct number of arguments
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <db file> <query file>" << std::endl;
        return -1;
    }

    // Data structures to store movie-actor relationships
    std::unordered_map<std::string, std::vector<std::string>> movieToActors;
    std::unordered_map<std::string, std::vector<std::string>> actorToMovies;
    std::string line, movie;
    std::regex delim("/");

    // Start timer for data structure creation
    auto start = std::chrono::high_resolution_clock::now();

    // Open the database file
    std::ifstream dbfile(argv[1]);
    if (!dbfile.is_open()) {
        std::cout << "Unable to open file: " << argv[1] << std::endl;
        return -1;
    }

    int recordCount = 0;
    // Read the database file line by line
    while (std::getline(dbfile, line)) {
        auto begin = std::sregex_token_iterator(line.begin(), line.end(), delim, -1);
        auto end = std::sregex_token_iterator();
        if (begin == end) continue;

        // First token is the movie name
        movie = *begin++;
        std::vector<std::string> actors;
        // Remaining tokens are actor names
        for (auto it = begin; it != end; ++it) {
            std::string actor = *it;
            actors.push_back(actor);
            actorToMovies[actor].push_back(movie);
        }
        movieToActors[movie] = actors;
        recordCount++;
    }
    dbfile.close();

    // End timer for data structure creation
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> creationTime = end - start;

    // Start timer for query processing
    start = std::chrono::high_resolution_clock::now();

    // Open the query file
    std::ifstream queryfile(argv[2]);
    if (!queryfile.is_open()) {
        std::cout << "Unable to open file: " << argv[2] << std::endl;
        return -1;
    }

    // Read the query file line by line
    while (std::getline(queryfile, line)) {
        // Check if the line is a movie name
        if (movieToActors.find(line) != movieToActors.end()) {
            std::cout << "Actors in movie \"" << line << "\":" << std::endl;
            for (const auto& actor : movieToActors[line]) {
                std::cout << "\t" << actor << std::endl;
            }
        // Check if the line is an actor name
        } else if (actorToMovies.find(line) != actorToMovies.end()) {
            std::cout << "Movies with actor \"" << line << "\":" << std::endl;
            for (const auto& movie : actorToMovies[line]) {
                std::cout << "\t" << movie << std::endl;
            }
        // If not found in either map
        } else {
            std::cout << "Not Found: " << line << std::endl;
        }
    }
    queryfile.close();

    // End timer for query processing
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> searchTime = end - start;

    // Calculate total time taken
    std::chrono::duration<double> totalTime = creationTime + searchTime;

    // Output statistics
    std::cout << "\n# of records: " << recordCount << std::endl;
    std::cout << "Time taken to create data structure: " << creationTime.count() << " seconds" << std::endl;
    std::cout << "Time taken to search: " << searchTime.count() << " seconds" << std::endl;
    std::cout << "Total time taken: " << totalTime.count() << " seconds" << std::endl;

    return 0;
}