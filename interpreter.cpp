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
std::string Interpreter::readFromDataset(std::string dataset_path) {
    return COMMAND_INVALID;
};

//================================================================================
// Private functions.
//================================================================================

// Create random game with maximum path length
void Interpreter::createGame(int length) {

};

// Create game starting at a specific title and ending at a specific title
void Interpreter::createGame(Vertex start, Vertex end) {

};

// Prints out valid paths to console
std::string Interpreter::getValidPathsStr() {
    return COMMAND_INVALID;
};

// Prints out current vertex state (Different if you are at beginning or ending node)
std::string Interpreter::getCurrentVertexStr() {
    return COMMAND_INVALID;
};