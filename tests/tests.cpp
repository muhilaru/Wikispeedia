#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../game.h"
#include "../interpreter.h"
#include "../graph.h"

TEST_CASE("THICCCCCOOOOO BAMBA") {

  REQUIRE( true == true);
}

TEST_CASE("generateMatrix Simple") {

  Game game("Color", "Leprechaun");

  game.addPage("Color");
  game.addPage("Rainbow");
  game.addPage("Leprechaun");

  game.addLink("Color", "Rainbow");
  game.addLink("Rainbow", "Leprechaun");

  std::vector<Vertex> articles = game.getArticles();
  Graph graph = game.getGraph();

  const int INF = 1e7;

  std::vector<std::vector<int>> expected {

    {0, 1, 2},
    {INF, 0, 1},
    {INF, INF, 0}
  };

  std::vector<std::vector<int>> actual = game.generateMatrix(graph, articles);

  REQUIRE(actual == expected);
}

TEST_CASE("generateMatrix Basic Case") {

  Game game("Color", "Leprechaun");

  game.addPage("Chan");
  game.addPage("Color");
  game.addPage("Forest");
  game.addPage("Rainbow");
  game.addPage("Leprechaun");

  game.addLink("Chan", "Forest");
  game.addLink("Chan", "Leprechaun");
  game.addLink("Chan", "Color");
  game.addLink("Color", "Rainbow");
  game.addLink("Rainbow", "Leprechaun");

  std::vector<Vertex> articles = game.getArticles();
  Graph graph = game.getGraph();

  const int INF = 1e7;

  std::vector<std::vector<int>> expected {

    {0, 1, 1, 2, 1},
    {INF, 0, INF, 1, 2},
    {INF, INF, 0, INF, INF},
    {INF, INF, INF, 0, 1},
    {INF, INF, INF, INF, 0}
  };

  std::vector<std::vector<int>> actual = game.generateMatrix(graph, articles);

  REQUIRE(actual == expected);
}

TEST_CASE("generateMatrix Complex Cycles Case") {

  Game game("Blue", "Purple");

  game.addPage("Blue");
  game.addPage("Red");
  game.addPage("Green");
  game.addPage("Purple");

  game.addLink("Blue", "Red");
  game.addLink("Red", "Blue");

  game.addLink("Blue", "Green");

  game.addLink("Blue", "Purple");
  game.addLink("Purple", "Blue");

  game.addLink("Red", "Green");
  game.addLink("Red", "Purple");
  game.addLink("Green", "Purple");

  std::vector<Vertex> articles = game.getArticles();
  Graph graph = game.getGraph();

  std::vector<std::vector<int>> expected {

    {0, 1, 1, 1},
    {1, 0, 1, 1},
    {2, 3, 0, 1},
    {1, 2, 2, 0}
  };

  std::vector<std::vector<int>> actual = game.generateMatrix(graph, articles);

  REQUIRE(actual == expected);
}
