#include "interpreter.h"
#include <fstream>
#include <sstream>
#include <iostream>

//================================================================================
// Public functions.
//================================================================================

// Default constructor with default ostream (std::cout).
Interpreter::Interpreter() {
    // game_ = new Game();
};

// Takes the initial input.
std::string Interpreter::processStartInput(std::string input) {
    if (input == "start") {
        createGame(MIN_GAME_SIZE);
        std::cout << "Reading dataset..." << std::endl;
        readFromDataset("data/articles.tsv", "data/links.tsv");
        std::cout << "Reading Floyd-Warshall Matrix..." << std::endl;
        readAdjacencyMatrix("data/shortest-path-distance-matrix.txt");
        return "Created game.";
    } else {
        return COMMAND_INVALID;
    }
};

// Takes the input during the game.
std::string Interpreter::processGameInput(std::string input) {
    return COMMAND_INVALID;
};

// Add all vertices and edges from dataset into game/graph.
// need to take in articles.tsv and links.tsv so I added one extra param
std::string Interpreter::readFromDataset(std::string articles_path, std::string links_path) {
    std::ifstream articles(articles_path);
    std::string line;
    while (std::getline(articles, line)) {
        if (line.size() > 0 && line[0] != '#') {
            game_->addPage(line);
        }
    }
    std::ifstream links(links_path);
    while (std::getline(links, line)) {
        if (line.size() > 0 && line[0] != '#') {
            std::istringstream line_stream(line);
            std::vector<std::string> pages;
            std::string page;
            while(std::getline(line_stream, page, '\t')) {
                pages.push_back(page);
            }
            game_->addLink(pages[0], pages[1]);
        }
    }
    return COMMAND_INVALID;
};

std::string Interpreter::readAdjacencyMatrix(std::string matrix_path) {
    std::ifstream matrix(matrix_path);
    std::string line;
    while (std::getline(matrix, line)) {
        if (line.size() > 0 && line[0] != '#') {
            std::cout << line << std::endl;
        }
    }
    return COMMAND_INVALID;
};

//================================================================================
// Private functions.
//================================================================================

// Create random game with maximum path length
void Interpreter::createGame(int length) {
    game_ = new Game();
};

// Create game starting at a specific title and ending at a specific title
void Interpreter::createGame(Vertex start, Vertex end) {
    game_ = new Game(start, end);
};

// Prints out valid paths to console
std::string Interpreter::getValidPathsStr() {
    string list_of_paths = "";
    for (unsigned k = 0; k < game_->getValidPaths().size(); k++) {
        list_of_paths += game_->getValidPaths()[k];
        
        if (k != game_->getValidPaths().size() - 1) {
            list_of_paths += "\n";
        }

    }
    
    return list_of_paths;
};

// Prints out current vertex state (Different if you are at beginning or ending node)
std::string Interpreter::getCurrentVertexStr() {
    return game_->getCurrVertex();
};