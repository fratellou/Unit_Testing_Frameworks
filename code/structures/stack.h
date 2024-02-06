#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

class StackNode {
 public:
  string data;
  StackNode *next;

  StackNode(const string value) : next(nullptr) { data = value; }
};

class Stack {
 private:
  int size;
  int printErrors = 1;  // A flag to control error message printing

 public:
  StackNode *head;
  Stack() : head(nullptr), size(0) {}

  ~Stack() {
    while (head) {
      StackNode *temp = head;
      head = head->next;
      delete temp;
    }
    size = 0;
  }

  void setPrintErrorsFalse() { printErrors = 0; }

  void setPrintErrorsTrue() { printErrors = 1; }

  int getPrintErrors() const { return printErrors; }

  void push(const string element);
  string pop();
};

// This function pushes an element onto the stack
void Stack::push(const string element) {
  StackNode *node = new StackNode(element);
  if (!head) {
    head = node;
  } else {
    node->next = head;
    head = node;
  }
  size++;
}

// This function pops an element from the stack
string Stack::pop() {
  if (!head) {
    if (getPrintErrors()) cerr << "Error: Stack is empty.";
    return "";
  } else {
    string element = head->data;
    StackNode *temp = head;
    head = head->next;
    delete temp;
    size--;
    return element;
  }
}

#endif
