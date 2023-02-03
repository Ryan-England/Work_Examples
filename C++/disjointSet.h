/**
  disjointSet.h makes a disjoint set. It is separate from any maze-making
  program.

  @author: Ryan England
  @status: COMPLETE
*/

#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <vector>
#include <iostream> //remove once testing is done.

class DisjointSet {
public:
  DisjointSet(int n = 1) {
    size = n;
    parent = std::vector<int> (n);
    rank = std::vector<int> (n);
    for (int i = 0; i < size; i++) {
      parent[i] = i;
      rank[i] = 0;
    }
  }

  /**
    Returns the parent of x.
    If the parent of x isn't x, then it sets it to the parent of the parent
    of x recursively.
    As such, the parent of x becomes the root of the set, no matter how far
    down the tree the root is.

    @param x The index to find the parent of.
  */
  int find(int x) {
    if (x < 0 || x >= parent.size()) {
      return -1;
    }
    if (x != parent[x]) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  bool same(int x, int y) {
    return (find(x) == find(y));
  }
  /**
    Unions two sets together.
    Union is a reserved word in c++, but onion isn't. So that's why this
    is named this way.
    Onions are a union of onion layers, if you think about it.

    @param x The first set to union.
    @param y The second set to union.
  */
  void onionUnion(int x, int y) {
    if (x < 0 || y < 0 || x >= parent.size() || y >= parent.size()) {
      return;
    }

    link(find(x), find(y));
  }

  int getSize() {
    return size;
  }

  /**
    Prints out the contents of the set.
  */
  void print() {
    std::cout << "Int  Parent  Rank" << std::endl;
    for (int i = 0; i < parent.size(); i++) {
      std::cout << i << "  " << parent[i] << "  " << rank[i] << std::endl;
    }
  }

  void reset(int n) {
    size = n;
    parent.clear();
    parent = std::vector<int> (n);
    rank.clear();
    rank = std::vector<int> (n);
    for (int i = 0; i < size; i++) {
      parent[i] = i;
      rank[i] = 0;
    }
  }
private:
  /**
    Unions two sets together. If the two sets are the same, then does nothing.
    If the two sets have the same rank, increases the rank of one of the
    sets.

    @param x The first set to union.
    @param y The second set to union.
  */
  void link(int x, int y) {
    if (x == y) {
      return;
    }
    if (rank[x] > rank[y]) {
      parent[y] = x;
      size--;
    } else {
      parent[x] = y;
      size--;
      if (rank[x] == rank[y]) {
        rank[y]++;
      }
    }
  }
  std::vector<int> parent;
  std::vector<int> rank;
  int size;
};

#endif
