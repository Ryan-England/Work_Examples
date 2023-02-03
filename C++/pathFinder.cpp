/**
  pathFinder.cpp takes a maze from makeAMaze.cpp, and finds a path from the
  beginning to the end.

  @author Ryan England
  @status IN_PROGRESS
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <cmath>

class BFS {
public:

  BFS(std::string data) {
    bool foundInvalidSquare = false;
    for (int i = 0; i < data.length(); i++) {
      int value = 0;
      if (data[i] == 'A' || data[i] == 'a') {
        value = 10;
      } else if (data[i] == 'B' || data[i] == 'b') {
        value = 11;
      } else if (data[i] == 'C' || data[i] == 'c') {
        value = 12;
      } else if (data[i] == 'D' || data[i] == 'd') {
        value = 13;
      } else if (data[i] == 'E' || data[i] == 'e') {
        value = 14;
      } else if (data[i] == 'F' || data[i] == 'f') {
        value = 15;
        foundInvalidSquare = true;
      } else {
        char rawData = data[i];
        value = rawData - '0';
      }
      maze.push_back(value);
      color.push_back(0);
      distance.push_back(5000);
      parent.push_back(-1);
    }
    sidelength = std::sqrt(data.length());
    if (foundInvalidSquare) {
      std::cout << "Warning! This maze isn't quite valid.\n"
      << "There is at least one square that isn't connected to any other.\n";
    }
  }

  /**
    Finds a path to every other square from the start square.

    @param start The value of the square to start from.
  */
  void search() {
    find(0); // The first square in the maze.
  }

  /**
    Prints the path from the beginning to the end.
  */
  void print() {
    int i = maze.size() - 1;
    std::vector<int> results;

    while (i >= 0) {
      int row = i / sidelength;
      int collumn = i % sidelength;
      results.push_back(row);
      results.push_back(collumn);
      i = parent[i];
    }

    for (int i = results.size() - 1; i >= 0; i= i - 2) {
      std::cout << "(" << results[i] << ", " << results[i-1] << ")\n";
    }
  }

  /**
    Prints the path from beginning to end, in a format that works with
    Jeff's maze viewer. (That is, in the format (y, x) instead of (x, y).)
  */

  void revPrint() {
    int i = maze.size() - 1;
    std::vector<int> results;

    while (i >= 0) {
      int row = i / sidelength;
      int collumn = i % sidelength;
      results.push_back(collumn);
      results.push_back(row);
      i = parent[i];
    }

    for (int i = results.size() - 1; i >= 0; i= i - 2) {
      std::cout << "(" << results[i] << ", " << results[i-1] << ")\n";
    }
  }

  /**
    Prints out the contents of maze, to ensure that we read it in correctly.
    Deprecated.


  void testPrint() {
    for (int i = 0; i < maze.size(); i++) {
      if (i % sidelength == 0) {
        std::cout << std::endl;
      }
      std::cout << maze[i] << " ";
    }
  }
  */

  /**
    Prints out the parents of each square in the maze. Deprecated.

  void testParent() {
    for (int i = 0; i < maze.size(); i++) {
      if (i % sidelength == 0) {
        std::cout << std::endl;
      }
      std::cout << parent[i] << " ";
    }
  }
  */

  /**
    Prints out the distance from each square in the maze. Deprecated.

  void testDistance() {
    for (int i = 0; i < maze.size(); i++) {
      if (i % sidelength == 0) {
        std::cout << std::endl;
      }
      std::cout << distance[i] << " ";
    }
  }
  */

private:

  /**
    Gets all the connections a square has based on it's maze value.
  */
  std::vector<int> getConnections(int index) {
    std::vector<int> neighbors;
    int square = maze[index];
    if ((square & 1) == 0 && index != maze.size() - 1) {
      // There isn't a wall on the right.
      neighbors.push_back(index + 1);
    }
    if ((square & 2) == 0) {
      // There isn't a wall below.
      neighbors.push_back(index + sidelength);
    }
    if ((square & 4) == 0 && index != 0) {
      // There isn't a wall to the left.
      neighbors.push_back(index - 1);
    }
    if ((square & 8) == 0) {
      // There isn't a wall above.
      neighbors.push_back(index - sidelength);
    }
    return neighbors;
  }

  /**
    Helper function for Search().
    Finds a path to every other square from the given square.

    @param start The index of the square to start from.
  */
  void find(int start) {
    // Preventing magic numbers and starting a queue.
    int white = 0;
    int gray = 1;
    int black = 2;
    std::queue<int> searching;

    // Initialization.
    for (int i = 0; i < maze.size(); i++) {
      color[i] = white;
      distance[i] = 5000;
      parent[i] = -1;
    }
    color[start] = gray;
    distance[start] = 0;
    parent[start] = -1;
    searching.push(start);

    // Main loop
    while (!searching.empty()) {
      int t = searching.front();
      std::vector<int> adjacent = getConnections(t);
      for (int v : adjacent) {
        if (color[v] == white) {
          color[v] = gray;
          searching.push(v);
          distance[v] = distance[t] + 1;
          parent[v] = t;
        } //if
      } // for
      color[t] = black;
      searching.pop();
    } // while
  }

  std::vector<int> maze;
  std::vector<int> color;
  std::vector<int> distance;
  std::vector<int> parent;
  int sidelength;
};

int main() {
  std::string fullMaze;
  std::string mazeRow;
  while (std::cin >> mazeRow) {
    fullMaze = fullMaze + mazeRow;
  }
  BFS bread(fullMaze);
  bread.search();
  bread.print();
}
