/**
  This program makes a maze using a disjoint set.

  @author Ryan England
  @status COMPLETE
*/

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include "disjointSet.h"

class MazeMaker {
public:
  MazeMaker(int size) {
    pathSensor.reset(size * size);
    sideLength = size;
    maze.push_back(11);
    for (int i = 1; i < size * size - 1; i++) {
      // This leaves off the start and endpoints
      maze.push_back(15);
    }
    maze.push_back(14);
  }

  /**
    Randomly constructs a maze by knocking out walls until all squares are in
    the same set.
  */
  void constructMaze() {
    // Make a vector of indexes from 0 to the end of maze's size.
    std::vector<int> access(maze.size());
    for (int i = 0; i < sideLength * sideLength; i++) {
      access[i] = i;
    }

    while (pathSensor.getSize() > 1) {
      // Shuffle access
      unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
      std::shuffle(access.begin(), access.end(), std::default_random_engine(seed));

      //For each index in Access, try to combine squares.
      for (int square : access) {
        unsigned squareRand = std::chrono::system_clock::now().time_since_epoch().count();
        std::vector<int> neighbors = getNeighbors(square);
        std::shuffle(neighbors.begin(), neighbors.end(), std::default_random_engine(squareRand));
        fuse(square, neighbors);
        fixIndex(square);
      }
    }
  }

  /**
    Prints out the maze to std::cout, in hexadecimal. (A-F replaces 10-15);
  */
  void print() {
    //std::cout << "Current maze: " << std::endl;
    for (int i = 0; i < maze.size(); i++) {
      if (maze[i] == 10) {
        std::cout << "A";
      } else if (maze[i] == 11) {
        std::cout << "B";
      } else if (maze[i] == 12) {
        std::cout << "C";
      } else if (maze[i] == 13) {
        std::cout << "D";
      } else if (maze[i] == 14) {
        std::cout << "E";
      } else if (maze[i] == 15) {
        std::cout << "F";
      } else {
        std::cout << maze[i];
      }

      if (i % sideLength == sideLength - 1) {
        std::cout << std::endl;
      }
    }
  }
private:
  /**
    Fuses two squares together. Feed in the vector you get from getNeighbors()
    into this for the best results.
    It tries all the neighbors, and stops when it finds one that is
    not part of the set.

    @param index The square to fuse.
    @param neighbors The squares to attempt to fuse to.
  */
  void fuse(int index, std::vector<int>& neighbors) {
    for (int i = 0; i < neighbors.size(); i++) {
      int other = neighbors[i];
      if (!pathSensor.same(index, other)) {
        pathSensor.onionUnion(index, other);
        if (other == index - 1) { // Neighbor is on the left
          maze[index] = maze[index] & 11; // All sides filled in except for left
          maze[other] = maze[other] & 14; // All but the right
        } else if (other == index - sideLength) { // Above
          maze[index] = maze[index] & 7; // All sides except the top
          maze[other] = maze[other] & 13; // All sides except the bottom
        } else if (other == index + 1) { // On the right
          maze[index] = maze[index] & 14;
          maze[other] = maze[other] & 11;
        } else if (other == index + sideLength) { // Neighbor is below
          maze[index] = maze[index] & 13;
          maze[other] = maze[other] & 7;
        } else {
          std::cout << "There was an error; two non-neighboring sqaures attempted to fuse." << std::endl;
        }
        return;
      }
    }
  }
  /**
    Makes a vector of every valid neighbor next to index x in the maze.

    @param x The index of the square to get the neighbors of.
    @return The vector containing the results.
  */
  std::vector<int> getNeighbors(int x) {
    std::vector<int> results;
    int left = x - 1;
    int top = x - sideLength;
    int right = x + 1;
    int bottom = x + sideLength;
    // Add to the vector
    if (! (x % sideLength == 0) ) {
      results.push_back(left);
    }
    if (! (x < sideLength)) {
      results.push_back(top);
    }
    if (! (x % sideLength == sideLength - 1)) {
      results.push_back(right);
    }
    if (! (x >= sideLength * sideLength - sideLength)) {
      results.push_back(bottom);
    }

    return results;
  }

  /**
    Fixes a square if it's on the edge of a maze so that it no longer lets you
    escape the maze.

    @param x The index to fix.
  */
  void fixIndex(int x) {
    if (x % sideLength == 0 && x != 0) {
      // On the left wall
      maze[x] = maze[x] | 4;
    }
    if (x < sideLength) {
      // On the top of the maze
      maze[x] = maze[x] | 8;
    }
    if (x % sideLength == sideLength - 1 && x != sideLength * sideLength - 1) {
      // On the right wall
      maze[x] = maze[x] | 1;
    }
    if (x >= sideLength * sideLength - sideLength) {
      // On the bottom
      maze[x] = maze[x] | 2;
    }
  }

  DisjointSet pathSensor;
  std::vector<int> maze;
  int sideLength;
};

int main(int argc, char **argv) {
  char *inChar = argv[1];
  int sizeOfSide = std::atoi(argv[1]);
  //std::cout << sizeOfSide << std::endl;
  if (sizeOfSide < 2) {
    std::cout << "That isn't enough room to make a maze." << std::endl;
    return -1;
  }
  MazeMaker maze(sizeOfSide);
  maze.constructMaze();
  maze.print();
}
