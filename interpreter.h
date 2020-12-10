#pragma once

#include <iostream>
#include <string>
#include "game.h"
#include "edge.h"

class Interpreter {
	public:
        const int MIN_GAME_SIZE = 10;
        const std::string COMMAND_INVALID = "[Wikispeedia] You entered an invalid command. Please try again.";

        // Default constructor that outputs messages to std::cout.
		Interpreter();
        // Takes the initial input, returns the output to the command line.
        std::string processStartInput(std::string input);
        // Takes the input during the game. Returns the output to the command line.
        std::string processGameInput(std::string input);
        // Add all vertices and edges from dataset into game/graph. Returns the output to the command line.
        std::string readFromDataset(std::string articles_path, std::string links_path);
		// Reads in an adjacency matrix from a file, rather than generating it (takes 40 mintutes on i7-10700k)
		std::string readAdjacencyMatrix(std::string matrix_path);
	private:
		Game* game_;

		// Create random game with maximum path length
		void createGame(int length);
		// Create game starting at a specific title and ending at a specific title
		void createGame(Vertex start, Vertex end);
		// Prints out valid paths to console
		std::string getValidPathsStr();
		// Prints out current vertex state (Different if you are at beginning or ending node)
		std::string getCurrentVertexStr();

		std::string getStatusStr();
};
