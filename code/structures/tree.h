#ifndef TREE_H
#define TREE_H

#include <iostream>
using namespace std;

class TreeNode {
 public:
  int key;
  TreeNode *left;
  TreeNode *right;
  TreeNode *parent;

  TreeNode(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}
};

class Tree {
 public:
  TreeNode *root;

  Tree() : root(nullptr) {}

  ~Tree() { clear(root); }

  void clear(TreeNode *node) {
    if (node) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  TreeNode *add(TreeNode *root, int key);
  TreeNode *search(TreeNode *root, int data);
  TreeNode *succ(TreeNode *root);
  TreeNode *del(TreeNode *root, int data);
  TreeNode *min(TreeNode *root);
  void transplant(TreeNode *&root, TreeNode *u, TreeNode *v);
  void print(TreeNode *tree, int space) const;
};

// Function to insert a new node with the given key into the tree
TreeNode *Tree::add(TreeNode *root, int key) {
  if (root == nullptr) return new TreeNode(key);

  TreeNode *current = root, *parent = nullptr;
  while (current != nullptr) {
    parent = current;
    if (key < current->key)
      current = current->left;
    else
      current = current->right;
  }

  TreeNode *newNode = new TreeNode(key);
  newNode->parent = parent;
  if (key < parent->key)
    parent->left = newNode;
  else
    parent->right = newNode;

  return root;
}

// Function to search for a node in the tree with the given key
TreeNode *Tree::search(TreeNode *root, int data) {
  if (root == nullptr || root->key == data) {
    return root;
  } else if (data < root->key) {
    return search(root->left, data);
  } else {
    return search(root->right, data);
  }
}

// Function to return the successor of a given node in the tree
TreeNode *Tree::succ(TreeNode *root) {
  if (root->right != nullptr) return min(root->right);

  TreeNode *p = root->parent;
  while (p != nullptr && root == p->right) {
    root = p;
    p = p->parent;
  }
  return p;
}

// Function to return the minimum value node in the tree
TreeNode *Tree::min(TreeNode *root) {
  while (root->left != nullptr) root = root->left;
  return root;
}

// Function to delete a node with the specified data from a binary search tree
TreeNode *Tree::del(TreeNode *root, int data) {
  TreeNode *nodeToDelete = search(root, data);
  if (nodeToDelete != nullptr) {
    if (nodeToDelete->left == nullptr && nodeToDelete->right == nullptr) {
      transplant(root, nodeToDelete, nullptr);
    } else if (nodeToDelete->left == nullptr) {
      transplant(root, nodeToDelete, nodeToDelete->right);
    } else if (nodeToDelete->right == nullptr) {
      transplant(root, nodeToDelete, nodeToDelete->left);
    } else {
      TreeNode *successor = succ(nodeToDelete);
      if (successor->parent != nodeToDelete) {
        transplant(root, successor, successor->right);
        successor->right = nodeToDelete->right;
        successor->right->parent = successor;
      }
      transplant(root, nodeToDelete, successor);
      successor->left = nodeToDelete->left;
      successor->left->parent = successor;
    }
    delete nodeToDelete;
  }
  return root;
}

// Function to transplant one subtree with another in the tree
void Tree::transplant(TreeNode *&root, TreeNode *u, TreeNode *v) {
  if (u->parent == nullptr) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  if (v != nullptr) {
    v->parent = u->parent;
  }
}

// Function to print the contents of a binary tree in a structured format
void Tree::print(TreeNode *tree, int space) const {
  if (tree == nullptr) {
    return;
  }
  space += 4;
  print(tree->right, space);
  cout << endl;
  for (int i = 4; i < space; i++) {
    cout << " ";
  }
  cout << tree->key << endl;
  print(tree->left, space);
}
#endif
