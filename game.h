#pragma once

#include "graph.h"
#include "edge.h"
#include <stack>
#include <vector>
#include <map>

/**
// The Game class keeps track of the user's movement throughout the graph, allowing them to traverse 
// to different Wikipedia pages in the graph. Also can generate an adjacency matrix for other games to use.
**/
class Game {
    public:
        // Creates game from random beginning and end.
        Game();
        // Creates game from predefined start and end.
        Game(Vertex start, Vertex end);
        // helper function to create random Game
        void createRandomGame();
        // uses existing matrix to calculate shortest path between start and end using Floyd
        int calculateShortestPath();
        // sets the maximum length of the optimal path
        void setMax(int m);
        // Create matrix based on graph’s current state using Floyd Warshall’s Algorithm
        std::vector<std::vector<int>> generateMatrix(Graph graph, std::vector<Vertex> articles);
        // Adds a vertex to the graph
        void addPage(Vertex vert);
        // Adds an edge to the graph
        void addLink(Vertex from, Vertex to);
        // Returns a list of all of the 
        std::vector<Vertex> getValidPaths();
        // Returns the destination title
        std::string getDestination();
       // Helper function of iteration deepening DFS
        bool IDDFS(Vertex begin, int maxDepth);
        // (TEST) Use iterative deepening DFS to find the most optimal path.
        std::vector<Vertex> getOptimumPath(int max_depth);
        // Use iterative deepening DFS to find the most optimal path.
        std::vector<Vertex> getOptimumPath();
        // Attempt to move to a specific page. Return true if moved to valid page.
        bool moveTo(Vertex to);
        // Returns true if a vertex was popped off the stack
        bool moveBack();
        // Returns true if at the final node
        bool isComplete();
        // Returns true if at the beginning node
        bool isAtStart();
        // Return current vertex
        string getCurrVertex();
        // Returns current graph
        Graph getGraph();
        // Resets instances variables to setup for a new game
        void resetGameState();
        // Prints out the user's path from start to end and the most optimal path
        std::string completedGame();
        // Loads in and saves generated matrix to matrix.txt
        void matrixToFile(std::vector<std::vector<int>> matrix);
        // Used to read in matrix and set values accordingly in the adjacency matrix instance variable
        void setMatrixEntry(int x, int y, char val);
        // returns the list of verticies (Wiki pages)
        std::vector<Vertex> getArticles();
	private:
        // instance variables to track the start, end, and current Wiki pages during a game
		Vertex start_;
		Vertex end_;
		Vertex current_;
        // graph to represent all nodes and edges in the Wikispeedia data set
		Graph graph_;
        // holds all nodes (Wiki pages) a user visits in order
		std::stack<Vertex> path_taken_;
        // the maximum length of the most optimal path from start to end (used when creating a new game)
        int max = 10;
        // used to represent disconnected nodes in the distance adjacency matrix
        const int INF = 1e7;
        // adjacency matrix to store all optimal path lengths from all possible start and end nodes
        std::vector<std::vector<int>> dist_matrix;
        // holds all verticies of graph (Wiki pages)
        std::vector<Vertex> articles;
        // maps verticies to indicies - used to access specific start and end nodes in the distance adjacency matrix
        std::map<Vertex, int> page_map;
        // initialized using iterative deepening DFS to calculate the shortest/most optimal path between two nodes (Wiki pages)
        std::stack<Vertex> optimal_path_taken_;
};
