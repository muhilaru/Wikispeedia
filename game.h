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
        // uses existing matrix to calculate shortest path between start and end using Floyd
        int calculateShortestPath();
        // Create matrix based on graph’s current state using Floyd Warshall’s Algorithm
        std::vector<std::vector<int>> generateMatrix(Graph graph, std::vector<Vertex> articles);
        // Reads in generated adjacency matrix
        void readAdjacencyMatrix(string matrix_path);
        // Adds a vertex to the graph
        void addPage(Vertex vert);
        // Adds an edge to the graph
        void addLink(Vertex from, Vertex to);
        // Returns a list of all of the 
        std::vector<Vertex> getValidPaths();
        // Use iterative deepening DFS to find the most optimal path.
        std::vector<Edge> getOptimiumPath();
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

        Graph getGraph();

        std::vector<Vertex> getArticles();
	private:

		Vertex start_;
		Vertex end_;
		Vertex current_;
		Graph graph_;
		std::stack<Vertex> path_taken_;

        // the maximum length of the most optimal path from start to end (used when creating a new game)
        int max = 20;

        const int INF = 1e7;
        //for generateMatrix() -- chan
        std::vector<std::vector<int>> dist_matrix;

        //I need the articles in order to use the indices for generateMatrix() -- chan
        std::vector<Vertex> articles;

        std::map<Vertex, int> page_map;
};