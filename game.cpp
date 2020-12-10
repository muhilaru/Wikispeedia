#include "game.h"
#include <cmath>

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

};

// helper function to create random Game
void Game::createRandomGame() {

    generateMatrix(graph_, articles);
    int random = rand() % articles.size();

    int reserve_i = -1;
    int reserve_j = -1;

    int index = 0;
    for (unsigned i = 0; i < dist_matrix.size(); i++) {
        for (unsigned j = 0; j < dist_matrix[i].size(); j++) {
            index++;

            if (index >= random && dist_matrix[i][j] <= max) {
               
                start_ = articles.at(i);
                current_ = start_;
                end_ = articles.at(j);

               path_taken_.push(start_);

               return;


            } else if (dist_matrix[i][j] <= max) {
                reserve_i = i;
                reserve_j = j;
            }
        }
    }

    if (reserve_i != -1 && reserve_j != -1) {

        start_ = articles.at(reserve_i);
        current_ = start_;
        end_ = articles.at(reserve_j);
        

        path_taken_.push(start_);
        return;

    } else {

        max = 20;
        createRandomGame();
    }

};

// uses existing matrix to calculate shortest path between start and end using Floyd
int Game::calculateShortestPath() {

    int start_index = page_map[start_];
    int end_index = page_map[end_];
    return dist_matrix[start_index][end_index];

};

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
    optimal_path_taken_.clear();
    createRandomGame();

}

//================================================================================
// Private functions.
//================================================================================

