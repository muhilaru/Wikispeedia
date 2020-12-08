#include "interpreter.h"

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
//need to take in articles.tsv and links.tsv so I added one extra param
std::string Interpreter::readFromDataset(std::string articles_path, std::string links_path) {

    return COMMAND_INVALID;
};

//================================================================================
// Private functions.
//================================================================================

// Create random game with maximum path length
void Interpreter::createGame(int length) {

    Game game;
    game_ = &game;

};

// Create game starting at a specific title and ending at a specific title
void Interpreter::createGame(Vertex start, Vertex end) {

    Game game(start, end);
    game_ = &game;

};

// Prints out valid paths to console
std::string Interpreter::getValidPathsStr() {
    return COMMAND_INVALID;
};

// Prints out current vertex state (Different if you are at beginning or ending node)
std::string Interpreter::getCurrentVertexStr() {
    return game_->getCurrVertex();
};