#include "game.h"
#include <cmath>
#include <ctime>

//================================================================================
// Public functions.
//================================================================================

// Creates game from random beginning and end.
Game::Game() {};

// Creates game from predefined start and end.
Game::Game(Vertex start, Vertex end) {
    start_ = start;
    end_ = end;
};

// helper function to create random Game
void Game::createRandomGame() {
    srand(time(NULL));
    int a = rand() % articles.size();
    int b = rand() % articles.size();
    while (a == b || dist_matrix[a][b] > max) {
        a = rand() % articles.size();
        b = rand() % articles.size();
    }
    start_ = articles.at(a);
    end_ = articles.at(b);
    current_ = articles.at(a);
    while (!path_taken_.empty()) {
        path_taken_.pop();
    }
    path_taken_.push(current_);
};

// uses existing matrix to calculate shortest path between start and end using Floyd
int Game::calculateShortestPath() {

    int start_index = page_map[start_];
    int end_index = page_map[end_];
    return dist_matrix[start_index][end_index];

};

// Loads in and saves generated matrix to matrix.txt
void Game::matrixToFile(std::vector<std::vector<int>> matrix) {

    std::ofstream file;
    file.open("matrix.txt");

    for (int i = 0; i < articles.size(); i++) {
        std::string line = "";
        for (int j = 0; j < articles.size(); j++) {
            if (matrix.at(i).at(j) == INF) {
                line += "_";
            } else {
                line += to_string(matrix.at(i).at(j));
            }
        }
        file << line << std::endl;
    }
}

// Create matrix based on graph’s current state using Floyd Warshall’s Algorithm
std::vector<std::vector<int>> Game::generateMatrix(Graph graph_, std::vector<Vertex> articles) {

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
            if (graph_.edgeExists(begin, end)) {
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
    matrixToFile(dist_matrix);
    return dist_matrix;
};

// Adds a vertex to the graph
void Game::addPage(Vertex vert) {
    graph_.insertVertex(vert);

    //need articles to be pushed in the order or the articles.tsv 
    articles.push_back(vert);

    //stores page to its index
    page_map.emplace(vert, articles.size() - 1);
};

// Adds an edge to the graph
void Game::addLink(Vertex from, Vertex to) {
    graph_.insertEdge(from, to);
};

// Returns a list of all of the 
std::vector<Vertex> Game::getValidPaths() {
    return graph_.getAdjacent(current_);
};

// Helper function of iteration deepening DFS
bool Game::IDDFS(Vertex begin, int maxDepth) {

    if (begin == end_) {
        return true;
    }
    if (maxDepth == 0) {
        return false;
    }

    auto adjNodes = graph_.getAdjacent(begin);
    for (unsigned i = 0; i < adjNodes.size(); i++) {
        if (IDDFS(adjNodes[i], maxDepth - 1)) {
            optimal_path_taken_.push(adjNodes[i]);
            return true;
        }
    }
    return false;
}

// Use iterative deepening DFS to find the most optimal path.
std::vector<Vertex> Game::getOptimumPath(int max_depth) {
    //IDDFS(start_, max_depth);
    
    for (int i = 0; i < max_depth + 4; i++) {
        IDDFS(start_, i);
        if (!optimal_path_taken_.empty()) {
            break;
        }
    }
    if (optimal_path_taken_.empty()) {
        return std::vector<Vertex>();
    }

    std::vector<Vertex> ret;
    ret.push_back(start_);

    while (!optimal_path_taken_.empty()) {    
        ret.push_back(optimal_path_taken_.top());
        optimal_path_taken_.pop();
    }

    return ret;
};

// Use iterative deepening DFS to find the most optimal path.
std::vector<Vertex> Game::getOptimumPath() {
    int start_ind = page_map[start_];
    int end_ind = page_map[end_];
    int max_depth = dist_matrix[start_ind][end_ind];
    return getOptimumPath(max_depth + 1);
}

// Attempt to move to a specific page. Return true if moved to valid page.
bool Game::moveTo(Vertex to) {
    if (graph_.edgeExists(current_, to)) {
        current_ = to;
        path_taken_.push(to);
        return true;
    }
    return false;
};

// Returns true if a vertex was popped off the stack
bool Game::moveBack() {

    if (path_taken_.size() > 1) {
        path_taken_.pop();
        current_ = path_taken_.top();
        return true;
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

// Returns current graph
Graph Game::getGraph() {
    return graph_;
}

// returns the list of verticies (Wiki pages)
std::vector<Vertex> Game::getArticles() {
    return articles;
}

// sets the maximum length of the optimal path
void Game::setMax(int m) {
    max = m;
}

// Resets instances variables to setup for a new game
void Game::resetGameState() {
    path_taken_ = std::stack<Vertex>();
    optimal_path_taken_ = std::stack<Vertex>();
    createRandomGame();
}

// Used to read in matrix and set values accordingly in the adjacency matrix instance variable
void Game::setMatrixEntry(int x, int y, char val) {
    int size = articles.size();
    if (dist_matrix.size() != size || dist_matrix[0].size() != size) {
        dist_matrix.resize(size, std::vector<int>(size, INF));
    }
    if (val != '_') {
        dist_matrix[x][y] = val - '0';
    }
};

// Returns the destination title
std::string Game::getDestination() {
    return end_;
};

// Prints out the user's path from start to end and the most optimal path
std::string Game::completedGame() {
    std::vector<Vertex> vert;
    path_taken_;
    std::string taken_str;
    std::string optimal_str;

    while (!path_taken_.empty()) {
        std::string title = path_taken_.top();
        path_taken_.pop();
        if (path_taken_.empty()) {
            taken_str = title + taken_str;
        } else {
            taken_str = " -> " + title + taken_str;
        }
    }

    std::vector<Vertex> path = getOptimumPath();

    for (int i = 0; i < path.size(); i++) {
        std::string title = path[i];
        if (i == 0) {
            optimal_str = title;
        } else {
            optimal_str = optimal_str + " -> " + title;
        }
    }

    current_ = end_;
    return "[Wikispeedia] Your path:\n" + taken_str + "\n[Wikispeedia] The optimal path:\n" + optimal_str + "\n[Wikispeedia] Press enter to play again.";
}

//================================================================================
// Private functions.
//================================================================================

