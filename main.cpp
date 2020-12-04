#include "game.h"
#include "interpreter.h"
#include "graph.h"
#include <iostream>


int main(int argc, char *argv[]) {

    argc = 0;
    argv = nullptr;

    std::cout << "Welcome to WikiSpeedia! Enter start to begin your game." << std::endl;

    string input;
    
    bool init = true;

    Interpreter interpreter;

    while (getline(std::cin, input) && input != "exit") {

      if (init) {
        std::cout << interpreter.processStartInput(input) << std::endl;
        init = false;
      } else {
        std::cout << interpreter.processGameInput(input) << std::endl;
      }

    }

  return 0;
}