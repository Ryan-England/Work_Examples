/**
  treeTest.cpp runs the binary search tree from binarySearchTree.cpp.

  @author Ryan England
  @status COMPLETE
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "binarySearchTree.h"

int main() {
  std::string content;
  std::string command;
  int number;
  std::string comment = "#";
  bool continueRunning = true;
  BinaryTree tree;

  while (continueRunning) {
    // std::cin >> command >> number;
    std::getline(std::cin, content);
    std::stringstream trace;
    trace.str(content);
    trace >> command >> number;

    if (command[0] != comment[0]) {
      if (command == "insert") {
        tree.insert(number);
      } else if (command == "delete") {
        tree.deleteData(number);
      } else if (command == "search") {
        tree.search(number);
      } else if (command == "predecessor") {
        tree.predecessor(number);
      } else if (command == "successor") {
        tree.successor(number);
      } else if (command == "min") {
        tree.min();
      } else if (command == "max") {
        tree.max();
      } else if (command == "inorder") {
        tree.inorderTraversal();
      } else if (command == "postorder") {
        tree.postorderTraversal();
      } else if (command == "preorder") {
        tree.preorderTraversal();
      } else if (command == "help") {
        std::cout << "The commands are: " << std::endl;
        std::cout << "(insert) (search) (predecessor) (successor) \n"
        << "(min) (max) (inorder) (postorder) (preorder)" << std::endl;
      } else {
        std::cout << "Command not recognized. Make sure you're only "
        << "using lowercase letters \nin your commands.\n";
        std::cout << "Type help for a list of commands.\n";
      }
    }
  }
}
