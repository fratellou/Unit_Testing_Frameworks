#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;

// Node class to represent individual elements in the linked list
class Node {
public:
    string element;
    Node* next;
    Node(const string& data) : element(data), next(nullptr) {}
};

// LinkedList class to encapsulate the linked list functionality
class LinkedList {
private:
    Node* head;
    int printErrors = 1; // A flag to control error message printing

public:
    
    // Constructor to initialize an empty linked list
    LinkedList() : head(nullptr) {}

    // Destructor to free the memory allocated for the entire linked list
    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;

            // Delete the node, which will invoke the Node destructor and free the string element
            delete temp;
        }
    }

    void setPrintErrorsFalse() {
        printErrors = 0;
    }

    void setPrintErrorsTrue() {
        printErrors = 1;
    }

    int getPrintErrors() {
        return printErrors;
    }

    void add(const string& data);
    void insert(const string& data, int index);
    void remove(string& element);
    void removeByIndex(int index, string& element);
    int removeByValue(const string& value); 
    int search(const string& element);
    void print();
};

// Function to add an element to the beginning of the list
void LinkedList::add(const string& data) {
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
}

// Function to insert an element at a specific index in the list
void LinkedList::insert(const string& data, int index) {
  if (index < 0) {
      if (getPrintErrors()) cerr << "Error: Negative index is not allowed.\n";
      return;
  }

  Node* newNode = new Node(data);
  if (head == nullptr && index == 0) {
      head = newNode;
  } else {
      Node* current = head;
      Node* previous = nullptr;
      int count = 0;

      // Traverse to the specified index
      while (current != nullptr && count < index) {
          previous = current;
          current = current->next;
          count++;
      }

      if (count == index) {
          // Insert the new node at the specified index
          newNode->next = current;
          if (previous != nullptr) {
              previous->next = newNode;
          } else {
              head = newNode;
          }
      } else {
        if (getPrintErrors()) cerr << "Error: Index is out of range.\n";
        return;
      }
  }
}

// Function to remove the first element from the list
void LinkedList::remove(string& element) {
    if (head == nullptr) {
        element = "";
        if (getPrintErrors()) cerr << "Error: List is empty\n";
    } else {
        Node* temp = head;
        element = temp->element;
        head = head->next;

        // Delete the node, which will invoke the Node destructor and free the string element
        delete temp;
    }
}

// Function to remove an element at a specific index from the list
void LinkedList::removeByIndex(int index, string& element) {
    if (index < 0) {
      element = "";
      if (getPrintErrors()) cerr << "Error: Negative index is not allowed.\n";
      return;
  }
    if (head == nullptr) {
        element = "";
        if (getPrintErrors()) cerr << "Error: List is empty\n";
    } else {
        Node* current = head;
        Node* previous = nullptr;
        int count = 0;

        // Traverse to the specified index
        while (current != nullptr && count < index) {
            previous = current;
            current = current->next;
            count++;
        }

        if (count == index) {
            // Remove the node at the specified index
            if (previous == nullptr) {
                element = head->element;
                head = current->next;
            } else {
                element = current->element;
                previous->next = current->next;

                // Delete the node, which will invoke the Node destructor and free the string element
                delete current;
            }
        } else {
            element = "";
            if (getPrintErrors()) cerr << "Error: Index is out of range.\n";
        }
    }
}

// Function to remove the first occurrence of a specific value from the list
int LinkedList::removeByValue(const string& value) {
    Node* current = head;
    Node* previous = nullptr;
    int result = 0;
    // Traverse the list to find the specified value
    while (current != nullptr && current->element != value) {
        previous = current;
        current = current->next;
    }

    if (current != nullptr) {
        // Remove the node with the specified value
        if (previous == nullptr) {
            head = current->next;
        } else {
            previous->next = current->next;

            // Delete the node, which will invoke the Node destructor and free the string element
            delete current;
            result = 1;
        }
    } else {
        if (getPrintErrors()) cerr << "Error: The element was not found.\n";
    }
    return result;
}


// Function to search for the index of a specific value in the list
int LinkedList::search(const string& value) {
    Node* current = head;
    int index = 0;

    // Traverse the list to find the specified value
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

// Function to print the elements of the list
void LinkedList::print() {
    Node* current = head;
    while (current != nullptr) {
        cout << current->element << " ";
        current = current->next;
    }
    cout << endl;
}

#endif
