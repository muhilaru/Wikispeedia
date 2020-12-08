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

  int count = 0;

  game.addPage("Color", count);
  game.addPage("Rainbow", count);
  game.addPage("Leprechaun", count);

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

  int count = 0;

  game.addPage("Chan", count);
  game.addPage("Color", count);
  game.addPage("Forest", count);
  game.addPage("Rainbow", count);
  game.addPage("Leprechaun", count);

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

  int count = 0;

  game.addPage("Blue", count);
  game.addPage("Red", count);
  game.addPage("Green", count);
  game.addPage("Purple", count);

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
