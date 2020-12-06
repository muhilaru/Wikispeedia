#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../game.h"
#include "../interpreter.h"
#include "../graph.h"

TEST_CASE("THICCCCCOOOOO BAMBA") {

  REQUIRE( true == true);
}

TEST_CASE("generateMatrix Basic Case") {

  Game game("Color", "Leprechaun");
  std::cout << "Hello!!" << std::endl;


  game.addPage("Chan");
  game.addPage("Color");
  game.addPage("Forest");
  game.addPage("Rainbow");
  game.addPage("Leprechaun");

  std::cout << "ADDED PAGES" << std::endl;

  game.addLink("Chan", "Forest");
  game.addLink("Chan", "Leprechaun");
  game.addLink("Chan", "Color");
  game.addLink("Color", "Rainbow");
  game.addLink("Rainbow", "Leprechaun");

  std::cout << "ADDED LINKS" << std::endl;

  std::vector<Vertex> articles = game.getArticles();
  Graph * graph = game.getGraph();

  std::cout << articles.size() << std::endl;

  const int INF = 1e7;

  std::vector<std::vector<int>> expected {

    {0, 1, 1, 2, 1},
    {INF, 0, INF, 1, 2},
    {INF, INF, 0, INF, INF},
    {INF, INF, INF, 0, 1},
    {INF, INF, INF, INF, 0}
  };

  std::vector<std::vector<int>> actual = game.generateMatrix(graph, articles);

  std::cout << actual.size() << std::endl;

  REQUIRE(actual == expected);

}
