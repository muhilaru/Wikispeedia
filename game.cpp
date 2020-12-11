#include "game.h"
#include <cmath>
#include <ctime>

//================================================================================
// Public functions.
//================================================================================

// Creates game from random beginning and end.
Game::Game() {
    
};

// Creates game from predefined start and end.
Game::Game(Vertex start, Vertex end) {

    // int start_index = page_map[start];
    // int end_index = page_map[end];

    // if (dist_matrix[start_index][end_index] <= max) {

    //     start_ = start;
    //     current_ = start;
    //     end_ = end;

    //     path_taken_.push(start);
    // } else {
    //     std::cout << "The length of most optimal path for the game you specified exceeds the maximum length threshold of " << max << "." << std::endl;
    //     std::cout << "A random game will now be created." << std::endl;
    //     createRandomGame();
    // }
    start_ = start;
    end_ = end;

};

// helper function to create random Game
void Game::createRandomGame() {
    srand(time(NULL));
    int a = rand() % articles.size();
    int b = rand() % articles.size();
    std::cout << a << "," << b << std::endl;
    while (a == b || dist_matrix[a][b] > max) {
        a = rand() % articles.size();
        b = rand() % articles.size();
    }
    start_ = articles.at(a);
    end_ = articles.at(b);
    current_ = articles.at(a);
};

// uses existing matrix to calculate shortest path between start and end using Floyd
int Game::calculateShortestPath() {

    int start_index = page_map[start_];
    int end_index = page_map[end_];
    return dist_matrix[start_index][end_index];

};

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

// Reads in generated adjacency matrix
void Game::readAdjacencyMatrix(string matrix_path) {

};

// Adds a vertex to the graph
void Game::addPage(Vertex vert) {
    graph_.insertVertex(vert);

    //I need articles to be pushed in the order or the articles.tsv --chan
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

bool Game::IDDFS(Vertex begin, int maxDepth) {
   // static std::unordered_set<Vertex> visited_;
  //  std::cout << begin << std::endl;
    //std::cout << maxDepth << std::endl;

    if (begin == end_) {
           // optimal_path_taken_.push_back(begin);
        std::cout << "Found end." << std::endl;
        return true;
    } 
    if (maxDepth == 0) {
        return false;
    } else if (maxDepth >= 0) {
        auto adjNodes = graph_.getAdjacent(begin);
        for (unsigned i = 0; i < adjNodes.size(); i++) {
            if (IDDFS(adjNodes[i], maxDepth - 1)) {
                optimal_path_taken_.push(adjNodes[i]);
                return true;
            } else {
                return false;
            }
        }
    } 

    return true;
}

// Use iterative deepening DFS to find the most optimal path.

std::vector<Vertex> Game::getOptimumPath(int max_depth) {
    // int start_ind = page_map[start_];
    // int end_ind = page_map[end_];
   

   
    IDDFS(start_, max_depth);
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

std::vector<Vertex> Game::getOptimumPath() {
    int start_ind = page_map[start_];
    int end_ind = page_map[end_];
    int max_depth = dist_matrix[start_ind][end_ind];
    return getOptimumPath(max_depth);
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

    if (!path_taken_.empty()) {
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

Graph Game::getGraph() {
    return graph_;
}

std::vector<Vertex> Game::getArticles() {
    return articles;
}

void Game::setMax(int m) {
    max = m;
}

void Game::resetGameState() {

    path_taken_ = std::stack<Vertex>();
    optimal_path_taken_ = std::stack<Vertex>();
    createRandomGame();

}

void Game::setMatrixEntry(int x, int y, char val) {
    int size = articles.size();
    if (dist_matrix.size() != size || dist_matrix[0].size() != size) {
        dist_matrix.resize(size, std::vector<int>(size, INF));
    }
    if (val != '_') {
        dist_matrix[x][y] = val - '0';
    }
};

std::string Game::getDestination() {
    return end_;
};

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
    std::cout << path.size() << std::endl;

    while (!optimal_path_taken_.empty()) {
        std::string title = optimal_path_taken_.top();
        path_taken_.pop();
        if (optimal_path_taken_.empty()) {
            optimal_str = title + optimal_str;
        } else {
            optimal_str = " -> " + title + optimal_str;
        }
    }

    return "[Wikispeedia] Your path:\n" + taken_str + "\n[Wikispeedia] The optimal path:\n" + optimal_str;
}

//================================================================================
// Private functions.
//================================================================================

