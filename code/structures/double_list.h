#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include <iostream>
using namespace std;

// Node class to represent individual elements in the doubly linked list
class DoubleNode {
 public:
  string element;
  DoubleNode* prev;
  DoubleNode* next;
  DoubleNode(const string& data)
      : element(data), prev(nullptr), next(nullptr) {}
};

// DoubleLinkedList class to encapsulate the double linked list functionality
class DoubleLinkedList {
 private:
  DoubleNode* head;
  DoubleNode* tail;
  int printErrors = 1;  // A flag to control error message printing

 public:
  // Constructor to initialize an empty double linked list
  DoubleLinkedList() : head(nullptr), tail(nullptr) {}

  // Destructor to free the memory allocated for the entire double linked list
  ~DoubleLinkedList() {
    while (head != nullptr) {
      DoubleNode* temp = head;
      head = head->next;

      // Delete the node, which will invoke the DoubleNode destructor and free
      // the string element
      delete temp;
    }
  }

  void setPrintErrorsFalse() { printErrors = 0; }

  void setPrintErrorsTrue() { printErrors = 1; }

  int getPrintErrors() { return printErrors; }

  void addToBeginning(const string& data);
  void addToEnd(const string& data);
  void removeByValue(const string& value, string& removedElement);
  void removeFromEnd(string& removedElement);
  int insertAtIndex(const string& data, int index);
  void removeFromBeginning(string& removedElement);
  void removeAtIndex(int index, string& removedElement);
  int search(const string& value);
};

// Function to add an element to the beginning of the double linked list
void DoubleLinkedList::addToBeginning(const string& data) {
  DoubleNode* newNode = new DoubleNode(data);
  if (head == nullptr) {
    head = tail = newNode;
  } else {
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
  }
}

// Function to add an element to the end of the double linked list
void DoubleLinkedList::addToEnd(const string& data) {
  DoubleNode* newNode = new DoubleNode(data);
  if (tail == nullptr) {
    head = tail = newNode;
  } else {
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
  }
}

// Removes given value from the doubly linked list
void DoubleLinkedList::removeByValue(const string& value,
                                     string& removedElement) {
  DoubleNode* current = head;
  while (current != nullptr && current->element != value) {
    current = current->next;
  }

  if (current != nullptr) {
    removedElement = current->element;

    if (current->prev != nullptr) {
      current->prev->next = current->next;
    } else {
      head = current->next;
    }

    if (current->next != nullptr) {
      current->next->prev = current->prev;
    } else {
      tail = current->prev;
    }

    delete current;
  } else {
    removedElement = "";
    if (getPrintErrors()) cerr << "Error: The element was not found.\n";
  }
}

// Function for adding an element by index
int DoubleLinkedList::insertAtIndex(const string& data, int index) {
  if (index < 0) {
    if (getPrintErrors()) cerr << "Error: Negative index is not allowed.\n";
    return 0;
  }
  DoubleNode* newNode = new DoubleNode(data);
  if (head == nullptr && index == 0) {
    head = tail = newNode;
    return 1;
  } else {
    DoubleNode* current = head;
    DoubleNode* previous = nullptr;
    int count = 0;
    while (current != nullptr && count < index) {
      previous = current;
      current = current->next;
      count++;
    }

    if (count == index) {
      newNode->next = current;
      newNode->prev = previous;

      if (current != nullptr) {
        current->prev = newNode;
      } else {
        tail = newNode;
      }

      if (previous != nullptr) {
        previous->next = newNode;
      } else {
        head = newNode;
      }
      return 1;
    } else {
      if (getPrintErrors()) cerr << "Error: Index is out of range.\n";
      delete newNode;
      return 0;
    }
  }
}

// Function to remove an item from the end of the list
void DoubleLinkedList::removeFromEnd(string& removedElement) {
  if (tail == nullptr) {
    removedElement = "";
    if (getPrintErrors()) cerr << "Error: List is empty.\n";
  } else {
    DoubleNode* lastNode = tail;
    removedElement = lastNode->element;

    if (lastNode->prev != nullptr) {
      lastNode->prev->next = nullptr;
      tail = lastNode->prev;
    } else {
      head = tail = nullptr;
    }

    delete lastNode;
  }
}

// Function to remove an item from the beginning of the list
void DoubleLinkedList::removeFromBeginning(string& removedElement) {
  if (head == nullptr) {
    removedElement = "";
    if (getPrintErrors()) cerr << "Error: List is empty\n";
  } else {
    DoubleNode* firstNode = head;
    removedElement = firstNode->element;

    head = head->next;

    if (head != nullptr) {
      head->prev = nullptr;
    } else {
      tail = nullptr;
    }

    delete firstNode;
  }
}

// Function for deleting an element by index
void DoubleLinkedList::removeAtIndex(int index, string& removedElement) {
  if (index < 0) {
    removedElement = "";
    if (getPrintErrors()) cerr << "Error: Negative index is not allowed.\n";
    return;
  }
  if (head == nullptr) {
    removedElement = "";
    if (getPrintErrors()) cerr << "Error: List is empty\n";
  } else {
    DoubleNode* current = head;
    DoubleNode* previous = nullptr;
    int count = 0;

    while (current != nullptr && count < index) {
      previous = current;
      current = current->next;
      count++;
    }

    if (count == index) {
      removedElement = current->element;

      if (previous == nullptr) {
        head = current->next;

        if (head != nullptr) {
          head->prev = nullptr;
        }
      } else {
        previous->next = current->next;

        if (current->next != nullptr) {
          current->next->prev = previous;
        } else {
          tail = previous;
        }
      }

      delete current;
    } else {
      removedElement = "";
      if (getPrintErrors()) cerr << "Error: Index is out of range.\n";
    }
  }
}

// Function to search for an item in the list
int DoubleLinkedList::search(const string& value) {
  DoubleNode* current = head;
  int index = 0;

  while (current != nullptr && current->element != value) {
    current = current->next;
    index++;
  }

  if (current == nullptr) {
    if (getPrintErrors()) cerr << "Error: Value not found.\n";
    return -1;
  } else {
    return index;
  }
}

#endif
