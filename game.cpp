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
std::vector<std::vector<int>> Game::generateMatrix(Graph * graph_, std::vector<Vertex> articles) {

    int size = articles.size();

    dist_matrix.resize(size, std::vector<int>(size, INF));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                dist_matrix.at(i).at(i) = 0;
                continue;
            }
            Vertex begin = articles.at(i);
            Vertex end = articles.at(j);
            if (graph_->edgeExists(begin, end)) {
                dist_matrix.at(i).at(j) = 1;
            }
        }
    }

    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {

                if (dist_matrix.at(i).at(k) + dist_matrix.at(k).at(j) < dist_matrix.at(i).at(j)) {
                    dist_matrix.at(i).at(j) = dist_matrix.at(i).at(k) + dist_matrix.at(k).at(j);
                }
            }
        }
    }
    return dist_matrix;
};

// Reads in generated adjacency matrix
void Game::readAdjacencyMatrix(string matrix_path) {

};

// Adds a vertex to the graph
void Game::addPage(Vertex vert) {
    graph_->insertVertex(vert);

    //I need articles to be pushed in the order or the articles.tsv --chan
    articles.push_back(vert);

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

    if (!path_taken_.empty()) {
        path_taken_.pop();
        current_ = path_taken_.top();
    }

    return false;
};

// Returns true if at the final node
bool Game::isComplete() {
    return current_ == end_;
};

// Returns true if at the beginning node
bool Game::isAtStart() {
    return current_ == start_;
};

// Returns the current vertex
string Game::getCurrVertex() {
    return current_;
}

//================================================================================
// Private functions.
//================================================================================

