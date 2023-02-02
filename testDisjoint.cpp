/** Just for testing the disjoint set.

  @author Ryan England
  @status COMPLETE
*/
#include <iostream>
#include "disjointSet.h"

int main() {
  std::cout << "The size of the set is 5." << std::endl;
  int size = 5;
  DisjointSet testing(size);
  testing.print();
  std::cout << "The parent of 1 is : " << testing.find(1) << std::endl;
  std::cout << "Uniting 1 and 4." << std::endl;
  testing.onionUnion(1, 4);
  std::cout << "Uniting 4 and 0." << std::endl;
  testing.onionUnion(4, 0);
  testing.onionUnion(2, 3);
  testing.onionUnion(2, 5);
  testing.print();
  testing.onionUnion(2, 4);
  std::cout << "The parent of 4 is: " << testing.find(4) << std::endl;
  std::cout << "The parent of 2 is: " << testing.find(2) << std::endl;
  testing.print();
}
