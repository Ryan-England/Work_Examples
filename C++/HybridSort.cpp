/**
  HybridSort.cpp

  A program that sorts input from cin, and outputs the results to cout.

  Author: Ryan England
  */
#include <iostream>
#include <iomanip>
#include <vector>

int findIth(int data, int whichDigit) {
  int digit;
  for (int k = 1; k <= whichDigit; k++) {
    digit = data % 10;
    data = data / 10;
  }
  // std::cout << "Ith digit: " << digit << std::endl;
  return digit;
}

/** void testing(std::vector<int> bucket) {
  std::cout << "Contents of bucket: ";
  for (int i = 0; i < bucket.size(); i++) {
    std::cout << bucket[i] << ", ";
  }
  std::cout << std::endl;
} */

void RadixBucketSort(std::vector<int> &A, int size) {
  int digits = 9;
  std::vector<std::vector<int>> bucket(10);
  for (int i = 1; i <= digits; i++) {
    //testing(A);
    for (int j = 0; j < size; j++) {
      int ith = findIth(A[j], i);
      bucket[ith].push_back(A[j]);
    }
    int k = 0;
    for (int j = 0; j < 10; j++) {
    // add items from bucket[j] into array A (overwriting them)
      for (int data : bucket[j]) {
        A[k] = data;
        k++;
        //std::cout << "Added " << data << " from bucket " << j << std::endl;
      }
    // clear buckets.
      bucket[j].clear();
    }
  }
}

int main() {
  std::vector<int> toSort;
  int data;
  while (std::cin >> data) {
    toSort.push_back(data);
  }
  RadixBucketSort(toSort, toSort.size());
  for (int i = 0; i < toSort.size(); ++i) {
    std::cout << std::setfill('0') << std::setw(9);
    std::cout << toSort[i] << std::endl;
  }
}
