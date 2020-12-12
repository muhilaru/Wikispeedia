#include "interpreter.h"
#include <fstream>
#include <sstream>
#include <iostream>

//================================================================================
// Public functions.
//================================================================================

// Default constructor with default ostream (std::cout).
Interpreter::Interpreter() {};

std::string Interpreter::processInput(std::string input) {
    if (!init_) {
        return processStartInput(input);
    } else {
        return processGameInput(input);
    }
};

// Takes the initial input.
std::string Interpreter::processStartInput(std::string input) {
    if (input == "READ") {
        createGame(MIN_GAME_SIZE);

        std::cout << "[Wikispeedia] Reading dataset..." << std::endl;
        readFromDataset("data/articles.tsv", "data/links.tsv");

        std::cout << "[Wikispeedia] Reading pre-generated matrix..." << std::endl;
        readAdjacencyMatrix("data/matrix.txt");

        std::cout << "[Wikispeedia] Creating game..." << std::endl;
        game_->createRandomGame();
        init_ = true;
        std::cout << "[Wikispeedia] Enter HELP to list all valid commands" << std::endl;
        return getStatusStr();
    } else if (input == "GENERATE") {
        createGame(MIN_GAME_SIZE);

        std::cout << "[Wikispeedia] Reading dataset..." << std::endl;
        readFromDataset("data/articles.tsv", "data/links.tsv");

        std::cout << "[Wikispeedia] Generating adjacency matrix... (WILL TAKE A LONG LONG LONG TIME)" << std::endl;;
        game_->generateMatrix(game_->getGraph(), game_->getArticles());
        game_->createRandomGame();
        init_ = true;
        std::cout << "[Wikispeedia] Enter HELP to list all valid commands" << std::endl;
        return getStatusStr();
    } else {
        init_ = false;
        return COMMAND_INVALID;
    }
};

// Takes the input during the game.
std::string Interpreter::processGameInput(std::string input) {
    if (game_->isComplete()) {
        game_->createRandomGame();
        return getStatusStr();
    } else {
        if (input == "HELP") {
            return "[Wikispeedia] Valid Commands:\n[Wikispeedia] GIVE UP - Will end current game and reveal the optimal solution path\n[Wikispeedia] BACK - Will return to the previous Wikipedia page visited\n[Wikispeedia] In order to move forward - enter the title of the page you'd like to travel EXACTLY how it appears in the list";
        } else if (input == "GIVE UP") {
            return game_->completedGame();
        } else if (input == "BACK") {
            game_->moveBack();
            return getStatusStr();
        } else if (game_->moveTo(input)) {
            return getStatusStr();
        } else {
            return COMMAND_INVALID;
        }
    }
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

// Reads in an adjacency matrix from a file, rather than generating it (takes 40 mintutes on i7-10700k)
std::string Interpreter::readAdjacencyMatrix(std::string matrix_path) {
    std::ifstream matrix(matrix_path);
    std::string line;
    int y = 0;
    while (std::getline(matrix, line)) {
        if (line.size() > 0 && line[0] != '#') {
            for (int x = 0; x < line.size(); x++){
                game_->setMatrixEntry(x, y, line[x]);
            }
            y++;
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
    string list_of_paths = "[Wikispeedia] You are able to travel to:\n\t";
    for (unsigned k = 0; k < game_->getValidPaths().size(); k++) {
        list_of_paths += game_->getValidPaths()[k];
        if (k != game_->getValidPaths().size() - 1) {
            list_of_paths += "\n\t";
        }
    }
    return list_of_paths;
};

// Prints out current vertex state (Different if you are at beginning or ending node)
std::string Interpreter::getCurrentVertexStr() {
    return "[Wikispeedia] You are currently at: " + game_->getCurrVertex() + "\n[Wikispeedia] Your target is: " + game_->getDestination();
};

// Returns "current status" string
std::string Interpreter::getStatusStr() {
    if (game_->isComplete()) {
        return game_->completedGame();
    } else {
        return getCurrentVertexStr() + "\n" + getValidPathsStr() + "\n[Wikispeedia] Enter the title of the page you'd like to travel:";
    }
};