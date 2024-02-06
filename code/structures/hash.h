// hash.h
#ifndef HASH_H
#define HASH_H

#include <iostream>
using namespace std;

class HashTableNode {
 public:
  string element;
  string key;
  HashTableNode *next;

  HashTableNode(const string k, const string val)
      : key(k), element(val), next(nullptr) {}
};

class HashTable {
 private:
  int size;
  int printErrors = 1;  // A flag to control error message printing

 public:
  HashTableNode **table;

  HashTable(int capacity = 100) : size(capacity) {
    table = new HashTableNode *[capacity]();
  }

  ~HashTable() {
    for (int i = 0; i < size; ++i) {
      HashTableNode *current = table[i];
      while (current) {
        HashTableNode *temp = current;
        current = current->next;
        delete temp;
      }
    }
    delete[] table;
  }

  void setPrintErrorsFalse() { printErrors = 0; }

  void setPrintErrorsTrue() { printErrors = 1; }

  int getPrintErrors() const { return printErrors; }

  int hash_calc(const string key) const;
  const string set(const string key, const string value);
  const string del(const string key);
  const string get(const string key) const;
};

// Function to calculate the hash value for a given key
int HashTable::hash_calc(const string key) const {
  int hash_val = 0;
  for (int i = 0; i < key.length(); i++) {
    hash_val += (int)key[i];
  }
  return hash_val % size;
}

// Function to insert or update a key-value pair in the hash table
const string HashTable::set(const string key, const string value) {
  int index = hash_calc(key);
  HashTableNode *newNode = new HashTableNode(key, value);

  if (table[index] == nullptr) {
    table[index] = newNode;
  } else {
    HashTableNode *current = table[index];
    while (current->next != nullptr) {
      if (current->key == key) {
        current->element = value;
        return current->element;
      }
      current = current->next;
    }
    current->next = newNode;
  }
  return newNode->element;
}

// Function to delete a key-value pair from the hash table
const string HashTable::del(const string key) {
  int index = hash_calc(key);
  if (table[index] == nullptr) {
    if (getPrintErrors()) cerr << "Error: key is empty.";
    return "";
  } else {
    HashTableNode *current = table[index];
    HashTableNode *prev = nullptr;
    while (current != nullptr) {
      if (current->key == key) {
        string element = current->element;
        if (prev == nullptr) {
          table[index] = current->next;
        } else {
          prev->next = current->next;
        }
        delete current;
        return element;
      }
      prev = current;
      current = current->next;
    }
  }
  return "";
}

// Retrieves an element from the hash table based on the provided key
const string HashTable::get(const string key) const {
  int index = hash_calc(key);
  HashTableNode *current = table[index];
  while (current != nullptr) {
    if (current->key == key) {
      return current->element;
    }
    current = current->next;
  }
  if (getPrintErrors()) cerr << "Error: key is empty";
  return "";
}

#endif
