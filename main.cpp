#include "game.h"
#include "interpreter.h"
#include "graph.h"
#include <iostream>


int main(int argc, char *argv[]) {

    argc = 0;
    argv = nullptr;

    std::cout << "[Wikispeedia] Welcome to Wikispeedia! Please type one of these commands EXACTLY to continue!" << std::endl;
    std::cout << "[Wikispeedia] GENERATE - Generates an adjacency matrix using the Floyd-Warshall algorithm. Will take a VERY VERY long time (30 minutes)." << std::endl;
    std::cout << "[Wikispeedia] READ - Reads in an adjacency matrix from a file, and starts the game. Super fast to start (3 seconds)." << std::endl;

    string input;
    Interpreter interpreter;

    while (getline(std::cin, input) && input != "EXIT") {
      std::cout << interpreter.processInput(input) << std::endl;
    }

  return 0;
}