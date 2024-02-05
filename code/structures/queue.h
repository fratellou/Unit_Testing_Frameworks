#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

class QueueNode {
public:
    string data;
    QueueNode *next;

    QueueNode(const string value) : next(nullptr) {
        data = value;
    }
};

class Queue {
private:
  int size;
  int printErrors = 1; // A flag to control error message printing

public:
    QueueNode *head;
    QueueNode *tail;

    Queue() : head(nullptr), tail(nullptr), size(0) {}

    ~Queue() {
        while (head) {
            QueueNode *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    void setPrintErrorsFalse() {
        printErrors = 0;
    }

    void setPrintErrorsTrue() {
        printErrors = 1;
    }

    int getPrintErrors() const {
        return printErrors;
    }

    void push(const string element);
    string pop();
};

// Push an element into the queue
void Queue::push(const string element) {
    QueueNode *node = new QueueNode(element);

    if (!head) {
        head = node;
        tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
    size++;
}

// Pop an element from the queue
string Queue::pop() {
    if (!head) {
        if (getPrintErrors()) cerr << "Error: Queue is empty.";
        return "";
    } else {
        string val = head->data;
        QueueNode *temp = head;
        head = head->next;
        size--;

        if (!head) {
            tail = nullptr;
        }

        delete temp;
        return val;
    }
}

#endif