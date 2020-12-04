#include "game.h"

//================================================================================
// Public functions.
//================================================================================

// Creates game from random beginning and end.
Game::Game() {

};

// Creates game from predefined start and end.
Game::Game(Vertex start, Vertex end) {

    start_ = start;
    current_ = start;
    end_ = end;

};

// uses existing matrix to calculate shortest path between start and end using Floyd
void Game::calculateShortestPath() {

};

// Create matrix based on graph’s current state using Floyd Warshall’s Algorithm
void Game::generateMatrix() {

};

// Reads in generated adjacency matrix
void Game::readAdjacencyMatrix(string matrix_path) {

};

// Adds a vertex to the graph
void Game::addPage(Vertex vert) {
    graph_->insertVertex(vert);

};

// Adds an edge to the graph
void Game::addLink(Vertex from, Vertex to) {
    graph_->insertEdge(from, to);

};

// Returns a list of all of the 
std::vector<Vertex> Game::getValidPaths() {
    return std::vector<Vertex>();
};

// Use iterative deepening DFS to find the most optimal path.
std::vector<Edge> Game::getOptimiumPath() {
    return std::vector<Edge>();
};

// Attempt to move to a specific page. Return true if moved to valid page.
bool Game::moveTo(Vertex to) {
    return false;
};

// Returns true if a vertex was popped off the stack
bool Game::moveBack() {
    return false;
};

// Returns true if at the final node
bool Game::isComplete() {
    return false;
};

// Returns true if at the beginning node
bool Game::isAtStart() {
    return false;
};

//================================================================================
// Private functions.
//================================================================================

