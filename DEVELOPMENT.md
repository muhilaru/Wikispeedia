**Week of 11/16:**

Our group decided on our Team Contract details and pushed into Github. We also finished writing our Project Goals and decided to use the WikiSpeedia dataset for our graph structure. For the algorithms of the project, we decided on using the iterative deepening DFS traversal, which counts as a traversal and algorithm and the Floyd Warshall algorithm. We highlighted key goals such as defining what we want for our Wikispeedia replica. We picked the terminal as our way of interacting with the game and chose to use the Floyd Warshall algorithm to find the distance between two pages and then we can determine the shortest way between pages using our DFS method. Next week, we will work on defining our classes, methods, and variables needed to execute this game and write some functionality for each class. 



**Week of 11/30:**

This week we defined the structure of the project and all of the necessary objects with their functions. This includes our main method, which constantly prompts the user for inputs. It also includes our “Interpreter” class, which converts the user’s input into game logic and can read in the dataset to the game. Our other class is the “Game” class, which keeps track of the user’s movements across the graph, can generate an adjacency matrix using the Floyd Warshall algorithm to compute distance between two nodes in constant time, and can determine the shortest path between two pages (nodes) using iterative deepening DFS traversal. We have a graph housed inside of the Game class, however this is the exact implementation that was used in lab_ml. At the time of writing this, we created all of the necessary files for our project, defined all of the functions that are necessary for every class to communicate with each other, and we are able to constantly read and process the user’s input. For next week, the big four things we need to do are read in the dataset, implement iterative deepening DFS for finding a solution, implement the Floyd Warshall algorithm to generate an adjacency matrix, and saving/reading the adjacency matrix to/from a file. Each of us are planning on taking one task each and we expect to finish this project on time.
