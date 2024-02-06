#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <stdexcept>
using namespace std;

class Array {
 private:
  int maxLen;
  int* data;
  int size;
  int printErrors = 1;  // A flag to control error message printing

 public:
  Array(int maxLen = 100) : size(0), maxLen(maxLen) { data = new int[maxLen]; }

  ~Array() { delete[] data; }

  void setPrintErrorsFalse() { printErrors = 0; }

  void setPrintErrorsTrue() { printErrors = 1; }

  int getPrintErrors() const { return printErrors; }

  int getMaxLen() const { return maxLen; }

  int add(int element);
  int insert(int index, int element);
  int removeLast();
  int removeAtIndex(int index);
  int get(int index) const;
  int change(int index, int element);
  int search(int element) const;
};

// Function to add an element to the end of the array
int Array::add(int element) {
  if (size < getMaxLen()) {
    data[size++] = element;
    return size;
  }
  if (getPrintErrors()) cerr << "Error: Array is full." << endl;
  return -1;
}

// Function to insert an element at a specific index in the array
int Array::insert(int index, int element) {
  if (index < 0) {
    if (getPrintErrors()) cerr << "Error: Negative index." << endl;
    return -1;
  }

  if (index > size) {
    if (getPrintErrors()) cerr << "Error: Index is out of size." << endl;
    return -1;
  }

  if (size < getMaxLen()) {
    for (int i = size; i > index; i--) {
      data[i] = data[i - 1];
    }
    data[index] = element;
    size++;
    return size;
  }
  if (getPrintErrors()) cerr << "Error: Array is full." << endl;
  return -1;
}

// Function to remove the last element in the array
int Array::removeLast() {
  if (size > 0) {
    return data[--size];
  }
  if (getPrintErrors()) cerr << "Error: Array is empty." << endl;
  return -1;
}

// Function to remove an element at a specific index in the array
int Array::removeAtIndex(int index) {
  if (index < 0) {
    if (getPrintErrors()) cerr << "Error: Negative index." << endl;
    return -1;
  }

  if (index > size) {
    if (getPrintErrors()) cerr << "Error: Index is out of size." << endl;
    return -1;
  }

  if (size > 0) {
    int element = data[index];
    for (int i = index; i < size - 1; i++) {
      data[i] = data[i + 1];
    }
    size--;
    return element;
  }
  if (getPrintErrors()) cerr << "Error: Array is empty." << endl;
  return -1;
}

// Function to get the value at a specific index in the array
int Array::get(int index) const {
  if (index < 0) {
    if (getPrintErrors()) cerr << "Error: Negative index." << endl;
    return -1;
  }
  if (index > size) {
    if (getPrintErrors()) cerr << "Error: Index is out of size." << endl;
    return -1;
  }
  return data[index];
}

// Function to change the value at a specific index in the array
int Array::change(int index, int element) {
  if (index < 0) {
    if (getPrintErrors()) cerr << "Error: Negative index." << endl;
    return -1;
  }
  if (index > size) {
    if (getPrintErrors()) cerr << "Error: Index is out of size." << endl;
    return -1;
  }

  data[index] = element;
  return element;
}

// Function to search for an element in the array and return its index
int Array::search(int element) const {
  for (int i = 0; i < size; i++) {
    if (data[i] == element) {
      return i;
    }
  }
  if (getPrintErrors()) cerr << "Error: Element not found." << endl;
  return -1;
}

#endif