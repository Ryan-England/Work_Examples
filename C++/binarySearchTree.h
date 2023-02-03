/**
  binarySearchTree.h is a program that stores integer values in a
    binary search tree.

  @author Ryan England
  @status COMPLETE
*/

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>

class BinaryTree {
  struct Node;
public:
  // Constructor
  BinaryTree() {
    root = nullptr;
  }

  // Destructor
  ~BinaryTree() {
    cull(root);
  }

  /**
    Searches the tree for a certain integer, then prints the result.

    @param key The integer to look for.
  */
  void search(int key) {
    Node *correctNode = find(root, key);
    if (correctNode == nullptr) {
      std::cout << key << " not found.\n";
    } else {
      std::cout << key << " found.\n";
    }
  }

  /**
    Inserts a value into the Binary Search Tree.

    @param key The value to insert.
  */
  void insert(int key) {
    Node *newNode = new Node(key);
    add(newNode);
    std::cout << "inserted " << key << ".\n";
  }

  /**
    Destroys a node in the tree with data equal to key.

    @param key the integer to remove from the tree.
  */
  void deleteData(int key) {
    Node *correctNode = find(root, key);
    if (correctNode == nullptr) {
      std::cout << "delete " << key << " - not found.\n";
    } else {
      remove(correctNode);
      std::cout << "deleted " << key << ".\n";
    }
  }

  /**
    Prints out the node with the smallest value in the tree.
  */
  void min() {
    Node *smallestNode = minimum(root);
    if (smallestNode == nullptr) {
      std::cout << "tree empty.\n";
    } else {
      std::cout << "min is " << smallestNode->key << ".\n";
    }
  }

  /**
    Prints out the node with the largest value in the tree.
  */
  void max() {
    Node *largestNode = maximum(root);
    if (largestNode == nullptr) {
      std::cout << "tree Empty.\n";
    } else {
      std::cout << "max is " << largestNode->key << ".\n";
    }
  }

  /**
    Finds and prints the predecessor to a number in the tree; AKA the
    next smallest number in the tree.

    @param key The number to search for.
  */
  void predecessor(int key) {
    Node *startingNode = find(root, key);
    if (startingNode == nullptr) {
      std::cout << key << " not in tree.\n";
    } else {
      Node *nextNode = prev(startingNode);
      if (nextNode == nullptr) {
        std::cout << "no predecessor for " << key << ".\n";
      } else {
        std::cout << key << " predecessor is " << nextNode->key << ".\n";
      }
    }
  }

  /**
    Finds and prints the successor to a number in the tree; AKA the next
    biggest number.

    @param key The number to search for.
  */
  void successor(int key) {
    Node *startingNode = find(root, key);
    if (startingNode == nullptr) {
      std::cout << key << " not in tree.\n";
    } else {
      Node *nextNode = next(startingNode);
      if (nextNode == nullptr) {
        std::cout << "no successor for " << key << ".\n";
      } else {
        std::cout << key << " successor is " << nextNode->key
          << ".\n";
      }
    }
  }

  /**
    Prints out the contents of the tree in order.
    See inorder().
  */
  void inorderTraversal() {
    std::cout << "inorder traversal:" << std::endl;
    inorder(root);
    std::cout << std::endl;
  }

  /**
    Prints out the contents of the tree with children printed after the
    parent node.
    See preorder.
  */
  void preorderTraversal() {
    std::cout << "preorder traversal:" << std::endl;
    preorder(root);
    std::cout << std::endl;
  }

  /**
    Prints out the contents of the tree with children printed before the
    parent node.
    See postorder.
  */
  void postorderTraversal() {
    std::cout << "postorder traversal:" << std::endl;
    postorder(root);
    std::cout << std::endl;
  }

  /**
    Helper function to print out single ints, followed by a space.
    Used by private functions.

    @param key The integer to print out.
  */
  void print(int &key) {
    std::cout << key << " ";
  }
private:
  /**
    Helper function for Search(). Works recursively.

    @param x The current node to check.
    @param key The integer to search for.
    @return The node that has the correct key, or nullptr if none was found.
  */
  Node* find(Node *x, int key) {
    if (x == nullptr || x->key == key) {
      return x;
    }

    if (key < x->key) {
      return find(x->left, key);
    } else {
      return find(x->right, key);
    }
  }

  /**
    Helper function for insert(). Adds the node to the tree.

    @param n The node to add to the tree.
  */
  void add(Node *n) {
    Node *parent = nullptr;
    Node *temp = root;

    // Finds where the node should be.
    while (temp != nullptr) {
      parent = temp;
      if (n->key < temp->key) {
        temp = temp->left;
      } else {
        temp = temp->right;
      }
    }

    // Adds node to tree
    n->parent = parent;
    if (parent == nullptr) {
      root = n;
      return;
    }
    if (n->key < parent->key) {
      parent->left = n;
    } else {
      parent->right = n;
    }
  }

  /**
    Helper function for deleteData(). Removes a node form the tree.

    @param n The node to remove.
  */
  void remove(Node *n) {
    Node *target = nullptr;;
    Node *x = nullptr;
    if (n->left == nullptr || n->right == nullptr) {
      target = n;
    } else {
      target = next(n);
    }
    if (target->left != nullptr) {
      x = target->left;
    } else {
      x = target->right;
    }
    if (x != nullptr) {
      x->parent = target->parent;
    }
    if (target->parent == nullptr) {
      root = x;
    } else if (target == target->parent->left) {
      target->parent->left = x;
    } else {
      target->parent->right = x;
    }
    if (target != n) {
      n->key = target->key;
    }
    delete target;
    return;
  }

  /**
    Helper function for min(). Returns the node with the smallest value in
    the tree.

    @param x The node to start looking from.
    @return The smallest node.
  */
  Node* minimum(Node *x) {
    while (x->left) {
      x = x->left;
    }
    return x;
  }

  /**
    Helper function for max(). Returns the node with the largest value
    in the tree.

    @param x The node to start looking from.
    @return The largest, grandest node.
  */
  Node* maximum(Node *x) {
    while (x->right) {
      x = x->right;
    }
    return x;
  }

  /**
    Helper function for predecessor. Find the last node in order.
    The parameter must be a valid node.

    @param x A valid node to find the next node from.
    @return The last node in line.
  */
  Node* prev(Node *x) {
    if (x->left != nullptr) {
      return maximum(x->left);
    }
    Node *temp = x->parent;
    while (temp != nullptr && x == temp->left) {
      x = temp;
      temp = temp->parent;
    }
    return temp;
  }

  /**
    Helper function for successor. Finds the next node in order.
    The parameter must be a valid node.

    @param x A valid node to find the next node from.
    @return The next node in line.
  */
  Node* next(Node *x) {
    if (x->right != nullptr) {
      return minimum(x->right);
    }
    Node *temp = x->parent;
    while (temp != nullptr && x == temp->right) {
      x = temp;
      temp = temp->parent;
    }
    return temp;
  }

  /**
    Helper function for inorderTraversal(). Works recursively.

    @param x A pointer to a node to print.
  */
  void inorder(Node *x) {
    if (x == nullptr) return;

    inorder(x->left);
    print(x->key);
    inorder(x->right);
  }

  /**
    Helper function for preorderTraversal(). Works recursively.

    @param x A pointer to a node to print.
  */
  void preorder(Node *x) {
    if (x == nullptr) return;

    print(x->key);
    preorder(x->left);
    preorder(x->right);
  }

  /**
    Helper function for postorderTraversal(). Works recursively.

    @param x A pointer to a node to print.
  */
  void postorder(Node *x) {
    if (x == nullptr) return;

    postorder(x->left);
    postorder(x->right);
    print(x->key);
  }

  void cull(Node *x) {
    if (x->left != nullptr) {
      cull(x->left);
    }
    if (x->right != nullptr) {
      cull(x->right);
    }
    remove(x);
  }

  Node *root;

  struct Node {
    Node(int initialData) {
      key = initialData;
      left = nullptr;
      right = nullptr;
      parent = nullptr;
    }
    Node& operator=(Node n) {
      key = n.key;
      left = n.left;
      right = n.right;
      parent = n.parent;
      return *this;
    }
    int key;
    Node *left;
    Node *right;
    Node *parent;
  };
};

#endif
