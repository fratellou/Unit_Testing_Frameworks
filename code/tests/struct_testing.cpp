#include <gtest/gtest.h>
#include "../structures/list.h"
#include "../structures/double_list.h"
#include "../structures/array.h"
#include "../structures/stack.h"
#include "../structures/queue.h"
#include "../structures/hash.h"
#include "../structures/tree.h"
using namespace std;

// ---------------------------------------------------------------

// Linked list: add command test
TEST(LinkedListTest, addTest) {
    LinkedList myList;
    myList.add(strdup("First"));
    myList.add(strdup("Second"));
    
    string top;
    myList.remove(top);

    ASSERT_EQ(top, "Second");
}

// Linked list: insert command test
TEST(LinkedListTest, InsTest) {
    LinkedList myList;
    myList.add(strdup("Third"));
    myList.add(strdup("First"));

    myList.insert(strdup("Second"), 1);

    string top;
    myList.remove(top);
    myList.remove(top);

    ASSERT_EQ(top, "Second");
}

// Linked list: insert command test - out of range
TEST(LinkedListTest, InsOutOfRange) {
    LinkedList myList;
    myList.setPrintErrorsFalse();
    myList.add(strdup("Third"));
    myList.add(strdup("First"));

    myList.insert(strdup("Second"), 4);

    string top;
    myList.remove(top);

    ASSERT_EQ(top, "First");
}

// Linked list: insert command test - negative index
TEST(LinkedListTest, InsNegativeIndex) {
    LinkedList myList;
    myList.setPrintErrorsFalse();
    myList.add(strdup("Third"));
    myList.add(strdup("First"));

    myList.insert(strdup("Second"), -5);

    string top;
    myList.remove(top);

    ASSERT_EQ(top, "First");
}

// Linked list: remove command test
TEST(LinkedListTest, RemTest) {
    LinkedList myList;
    myList.add(strdup("First"));
    myList.add(strdup("Second"));

    string element;
    myList.remove(element);

    ASSERT_EQ(element, "Second");
}

// Linked list: remove command test - empty list
TEST(LinkedListTest, RemEmptyList) {
    LinkedList myList;
    myList.setPrintErrorsFalse();

    string element = "";
    myList.remove(element);

    ASSERT_EQ(element, "");
}

// Linked list: removeByIndex command test
TEST(LinkedListTest, RemBITest) {
    LinkedList myList;
    myList.add(strdup("First"));
    myList.add(strdup("Second"));

    string element;
    myList.removeByIndex(1, element);

    ASSERT_EQ(element, "First");
}

// Linked list: removeByIndex command test - empty list
TEST(LinkedListTest, RemBIEmptyList) {
    LinkedList myList;
    myList.setPrintErrorsFalse();

    string element = "";
    myList.removeByIndex(1, element);

    ASSERT_EQ(element, "");
}

// Linked list: removeByIndex command test - negative index
TEST(LinkedListTest, RemBINegativeIndex) {
    LinkedList myList;
    myList.setPrintErrorsFalse();

    string element = "";
    myList.removeByIndex(-1, element);

    ASSERT_EQ(element, "");
}

// Linked list: removeByValue command test
TEST(LinkedListTest, RemBVTest) {
    LinkedList myList;
    myList.add(strdup("First"));
    myList.add(strdup("Second"));

    myList.removeByValue("Second");

    string top;
    myList.remove(top);

    ASSERT_EQ(top, "First");
}

// Linked list: removeByValue command test - empty list
TEST(LinkedListTest, RemBVEmptyList) {
    LinkedList myList;
    myList.setPrintErrorsFalse();

    int result = myList.removeByValue("Second");

    ASSERT_EQ(result, 0);
}

// Linked list: removeByValue command test - not found
TEST(LinkedListTest, RemBVNotFound) {
    LinkedList myList;
    myList.setPrintErrorsFalse();
    myList.add(strdup("First"));

    int result = myList.removeByValue("Second");

    ASSERT_EQ(result, 0);
}

// Linked list: search command test 
TEST(LinkedListTest, SearchTest) {
    LinkedList myList;
    myList.add(strdup("First"));
    myList.add(strdup("Second"));

    int result = myList.search("Second");

    ASSERT_EQ(result, 0);
}

// Linked list: search command test - not found
TEST(LinkedListTest, SearchTestNotFound) {
    LinkedList myList;
    myList.setPrintErrorsFalse();
    myList.add(strdup("First"));

    int result = myList.search("Second");

    ASSERT_EQ(result, -1);
}

// ---------------------------------------------------------------

// Doubly linked list: addToBeginning command test
TEST(DoubleLinkedListTest, addTBTest) {
    DoubleLinkedList myList;
    myList.addToBeginning(strdup("Second"));
    myList.addToBeginning(strdup("First"));
    
    
    string begin;
    myList.removeFromBeginning(begin);

    ASSERT_EQ(begin, "First");
}

// Doubly linked list: addToEnd command test
TEST(DoubleLinkedListTest, addTETest) {
    DoubleLinkedList myList;
    myList.addToEnd(strdup("First"));
    myList.addToEnd(strdup("Second"));
    
    
    string end;
    myList.removeFromEnd(end);

    ASSERT_EQ(end, "Second");
}

// Doubly linked list: removeByValue command test
TEST(DoubleLinkedListTest, removeByValueTest) {
    DoubleLinkedList myList;
    myList.addToBeginning("First");
    myList.addToBeginning("Second");
    myList.addToBeginning("Third");

    string removedElement;
    myList.removeByValue("Second", removedElement);

    ASSERT_EQ(removedElement, "Second");
}

// Doubly linked list: removeByValue command test - not found
TEST(DoubleLinkedListTest, removeByValueTestNotFound) {
    DoubleLinkedList myList;
    myList.addToBeginning("First");
    myList.addToBeginning("Second");
    myList.addToBeginning("Third");
    myList.setPrintErrorsFalse();

    string removedElement;
    myList.removeByValue("Fourth", removedElement);

    ASSERT_EQ(removedElement, "");
}

// Doubly linked list: insertAtIndex command test
TEST(DoubleLinkedListTest, insertAtIndexTest) {
    DoubleLinkedList myList;
    myList.addToEnd("First");
    myList.addToEnd("Second");

    myList.insertAtIndex("Third", 2);

    string result;
    myList.removeFromEnd(result);

    ASSERT_EQ(result, "Third");
}

// Doubly linked list: insertAtIndex command test - out of range
TEST(DoubleLinkedListTest, insertAtIndexTestOutOfRange) {
    DoubleLinkedList myList;
    myList.addToEnd("First");
    myList.addToEnd("Second");
    myList.setPrintErrorsFalse();
    int error_insert = myList.insertAtIndex("Third", 3);

    ASSERT_EQ(error_insert, 0);
}

// Doubly linked list: insertAtIndex command test - negative index
TEST(DoubleLinkedListTest, insertAtIndexTestNegativeIndex) {
    DoubleLinkedList myList;
    myList.addToEnd("First");
    myList.addToEnd("Second");
    myList.setPrintErrorsFalse();
    int error_insert = myList.insertAtIndex("Third", -1);

    ASSERT_EQ(error_insert, 0);
}

// Doubly linked list: removeFromEnd command test
TEST(DoubleLinkedListTest, removeFromEndTest) {
    DoubleLinkedList myList;
    myList.addToEnd("First");
    myList.addToEnd("Second");

    string removedElement;
    myList.removeFromEnd(removedElement);

    ASSERT_EQ(removedElement, "Second");
}

// Doubly linked list: removeFromEnd command test - empty list
TEST(DoubleLinkedListTest, removeFromEndTestEmptyList) {
    DoubleLinkedList myList;
    myList.setPrintErrorsFalse();
    string removedElement;
    myList.removeFromEnd(removedElement);

    ASSERT_EQ(removedElement, "");
}

// Doubly linked list: removeFromBeginning command test
TEST(DoubleLinkedListTest, removeFromBeginningTest) {
    DoubleLinkedList myList;
    myList.addToEnd("First");
    myList.addToEnd("Second");

    string removedElement;
    myList.removeFromBeginning(removedElement);

    ASSERT_EQ(removedElement, "First");
}

// Doubly linked list: removeFromBeginning command test - empty list
TEST(DoubleLinkedListTest, removeFromBeginningTestEmptyList) {
    DoubleLinkedList myList;
    myList.setPrintErrorsFalse();
    string removedElement;
    myList.removeFromEnd(removedElement);

    ASSERT_EQ(removedElement, "");
}

// Doubly linked list: removeAtIndex command test
TEST(DoubleLinkedListTest, removeAtIndexTest) {
    DoubleLinkedList myList;
    myList.addToEnd("First");
    myList.addToEnd("Second");
    myList.addToEnd("Third");

    string removedElement;
    myList.removeAtIndex(1, removedElement);

    ASSERT_EQ(removedElement, "Second");
}

// Doubly linked list: removeAtIndex command test - negative index
TEST(DoubleLinkedListTest, removeAtIndexTestNegativeIndex) {
    DoubleLinkedList myList;
    myList.addToEnd("First");
    myList.setPrintErrorsFalse();

    string removedElement;
    myList.removeAtIndex(-1, removedElement);

    ASSERT_EQ(removedElement, "");
}

// Doubly linked list: removeAtIndex command test - empty list
TEST(DoubleLinkedListTest, removeAtIndexTestEmptyList) {
    DoubleLinkedList myList;
    myList.setPrintErrorsFalse();
    string removedElement;
    myList.removeAtIndex(0, removedElement);

    ASSERT_EQ(removedElement, "");
}

// Doubly linked list: removeAtIndex command test - out of range
TEST(DoubleLinkedListTest, removeAtIndexTestOutOfRange) {
    DoubleLinkedList myList;
    myList.addToEnd("First");
    myList.setPrintErrorsFalse();

    string removedElement;
    myList.removeAtIndex(2, removedElement);

    ASSERT_EQ(removedElement, "");
}

// Doubly linked list: search command test
TEST(DoubleLinkedListTest, searchTest) {
    DoubleLinkedList myList;
    myList.addToEnd("First");
    myList.addToEnd("Second");
    myList.addToEnd("Third");

    int index = myList.search("Second");

    ASSERT_EQ(index, 1);
}

// Doubly linked list: search command test - not found
TEST(DoubleLinkedListTest, searchTestNotFound) {
    DoubleLinkedList myList;
    myList.addToEnd("First");
    myList.addToEnd("Second");
    myList.setPrintErrorsFalse();
    int index = myList.search("Third");

    ASSERT_EQ(index, -1);
}

// ---------------------------------------------------------------

// Array: add command test
TEST(ArrayTest, addTest) {
    Array myArray;
    ASSERT_EQ(myArray.add(5), 1);
}

// Array: add command test - full array
TEST(ArrayTest, addTestFullArray) {
    Array myArray(1);
    myArray.setPrintErrorsFalse();
    myArray.add(2);
    int result = myArray.add(5);

    ASSERT_EQ(result, -1);

}

// Array: insert command test
TEST(ArrayTest, insertTest) {
    Array myArray;
    myArray.add(5);
    myArray.add(15);
    myArray.insert(1, 10);

    int element =  myArray.get(1);
    ASSERT_EQ(element, 10);
}

// Array: insert command test - negative index
TEST(ArrayTest, insertTestNegativeIndex) {
    Array myArray;
    myArray.setPrintErrorsFalse();
    myArray.add(5);
    myArray.add(15);
    int error_insert = myArray.insert(-1, 10);

    ASSERT_EQ(error_insert, -1);
}

// Array: insert command test - full array
TEST(ArrayTest, insertTestFullArray) {
    Array myArray(1);
    myArray.setPrintErrorsFalse();
    myArray.add(5);
    int error_insert = myArray.insert(1, 10);

    ASSERT_EQ(error_insert, -1);
}

// Array: insert command test - out of size
TEST(ArrayTest, insertTestOutOfSize) {
    Array myArray;
    myArray.setPrintErrorsFalse();
    myArray.add(5);
    int error_insert = myArray.insert(2, 10);

    ASSERT_EQ(error_insert, -1);
}

// Array: removeLast command test
TEST(ArrayTest, removeLastTest) {
    Array myArray;
    myArray.add(5);

    ASSERT_EQ(myArray.removeLast(), 5);
}

// Array: removeLast command test - empty array
TEST(ArrayTest, removeLastTestEmptyArray) {
    Array myArray;
    myArray.setPrintErrorsFalse();

    ASSERT_EQ(myArray.removeLast(), -1);
}

// Array: removeAtIndex command test
TEST(ArrayTest, removeAtIndexTest) {
    Array myArray;
    myArray.add(5);
    myArray.add(10);
    myArray.add(15);

    ASSERT_EQ(myArray.removeAtIndex(1), 10);
}

// Array: removeAtIndex command test - negative index
TEST(ArrayTest, removeAtIndexTestNegativeIndex) {
    Array myArray;
    myArray.setPrintErrorsFalse();
    myArray.add(5);

    ASSERT_EQ(myArray.removeAtIndex(-1), -1);
}

// Array: removeAtIndex command test - out of size
TEST(ArrayTest, removeAtIndexTestOutOfSize) {
    Array myArray;
    myArray.setPrintErrorsFalse();
    myArray.add(5);

    ASSERT_EQ(myArray.removeAtIndex(2), -1);
}

// Array: removeAtIndex command test - empty array
TEST(ArrayTest, removeAtIndexTestEmptyArray) {
    Array myArray;
    myArray.setPrintErrorsFalse();

    ASSERT_EQ(myArray.removeAtIndex(0), -1);
}

// Array: get command test
TEST(ArrayTest, getTest) {
    Array myArray;
    myArray.add(5);
    myArray.add(10);
    myArray.add(15);

    int element = myArray.get(1);

    ASSERT_EQ(element, 10);
}

// Array: get command test - negative index
TEST(ArrayTest, getTestNegativeIndex) {
    Array myArray;
    myArray.setPrintErrorsFalse();
    myArray.add(5);
    myArray.add(10);
    myArray.add(15);

    int element = myArray.get(-1);
    
    ASSERT_EQ(element, -1);
}

// Array: get command test - out of size
TEST(ArrayTest, getTestOutOfSize) {
    Array myArray;
    myArray.setPrintErrorsFalse();
    myArray.add(5);

    int element = myArray.get(2);

    ASSERT_EQ(element, -1);
}

// Array: change command test
TEST(ArrayTest, changeTest) {
    Array myArray;
    myArray.add(5);
    myArray.add(10);
    myArray.add(15);

    ASSERT_EQ(myArray.change(1, 20), 20);

    int element =  myArray.get(1);
   
    ASSERT_EQ(element, 20);
}

// Array: change command test - negative index
TEST(ArrayTest, changeTestNegativeIndex) {
    Array myArray;
    myArray.setPrintErrorsFalse();
    myArray.add(5);

    ASSERT_EQ(myArray.change(-1, 20), -1);
}

// Array: change command test - out of size
TEST(ArrayTest, changeTestOutOfSize) {
    Array myArray;
    myArray.setPrintErrorsFalse();
    myArray.add(5);

    ASSERT_EQ(myArray.change(2, 20), -1);
}

// Array: search command test
TEST(ArrayTest, searchTest) {
    Array myArray;
    myArray.add(5);
    myArray.add(10);

    ASSERT_EQ(myArray.search(10), 1);
}

// Array: search command test - not found
TEST(ArrayTest, searchTestNotFound) {
    Array myArray;
    myArray.setPrintErrorsFalse();
    myArray.add(5);

    ASSERT_EQ(myArray.search(10), -1);
}

// ---------------------------------------------------------------

// Stack: push command test
TEST(StackTest, pushTest) {
    Stack myStack;
    myStack.push("First");
    myStack.push("Second");

    ASSERT_EQ(myStack.head->data, "Second");
}

// Stack: pop command test
TEST(StackTest, popTest) {
    Stack myStack;
    myStack.push("First");
    myStack.push("Second");

    string deleted = myStack.pop();
    ASSERT_EQ(deleted, "Second");
}

// Stack: pop command test - empty stack
TEST(StackTest, popTestEmptyStack) {
    Stack myStack;
    myStack.setPrintErrorsFalse();

    string deleted = myStack.pop();
    ASSERT_EQ(deleted, "");
}

// ---------------------------------------------------------------

// Queue: push command test
TEST(QueueTest, pushTest) {
    Queue myQueue;
    myQueue.push("First");
    myQueue.push("Second");

    ASSERT_EQ(myQueue.head->data, "First");
    ASSERT_EQ(myQueue.tail->data, "Second");
}

// Queue: pop command test
TEST(QueueTest, popTest) {
    Queue myQueue;
    myQueue.push("First");
    myQueue.push("Second");

    string deleted = myQueue.pop();
    ASSERT_EQ(deleted, "First");
}

// Queue: pop command test - empty queue
TEST(QueueTest, popTestEmptyQueue) {
    Queue myQueue;
    myQueue.setPrintErrorsFalse();

    string deleted = myQueue.pop();
    ASSERT_EQ(deleted, "");
}

// ---------------------------------------------------------------

// Hash table: set command test
TEST(HashTableTest, setTest) {
    HashTable myHashTable;
    myHashTable.set("key1", "First");
    myHashTable.set("key2", "Second");

    ASSERT_EQ(myHashTable.get("key1"), "First");
}

// Hash table: set command test - values with one key
TEST(HashTableTest, setTestValuesWithOneKey) {
    HashTable myHashTable;
    myHashTable.set("key1", "First");
    string value = myHashTable.set("key1", "Second");

    ASSERT_EQ(value, "Second");
}

// Hash table: set command test - keys with one hashes
TEST(HashTableTest, setTestKeysWithOneHashes) {
    HashTable myHashTable(1);
    myHashTable.set("a", "First");
    string value = myHashTable.set("abc", "Second");

    ASSERT_EQ(value, "Second");
}

// Hash table: del command test
TEST(HashTableTest, delTest) {
    HashTable myHashTable;
    myHashTable.set("key1", "First");
    string deleted_value = myHashTable.del("key1");

    ASSERT_EQ(deleted_value, "First");
}

// Hash table: del command test - empty key
TEST(HashTableTest, delTestEmptyKey) {
    HashTable myHashTable;
    myHashTable.setPrintErrorsFalse();
    string deleted_value = myHashTable.del("key1");

    ASSERT_EQ(deleted_value, "");
}

// Hash table: del command test - one key
TEST(HashTableTest, delTestOneKey) {
    HashTable myHashTable;
    myHashTable.set("key1", "First");
    myHashTable.set("key1", "Second");
    string deleted_value = myHashTable.del("key1");

    ASSERT_EQ(deleted_value, "First");
}

// Hash table: hash_calc command test
TEST(HashTableTest, hash_calcTest) {
    HashTable myHashTable;
    int hash = myHashTable.hash_calc("A");

    ASSERT_EQ(hash, 65);
}

// Hash table: get command test
TEST(HashTableTest, getTest) {
    HashTable myHashTable;
    myHashTable.set("key1", "First");
    string searched_value = myHashTable.get("key1");

    ASSERT_EQ(searched_value, "First");
}

// Hash table: get command test - empty key
TEST(HashTableTest, getTestEmptyKey) {
    HashTable myHashTable;
    myHashTable.setPrintErrorsFalse();
    string searched_value = myHashTable.get("key1");

    ASSERT_EQ(searched_value, "");
}

// ---------------------------------------------------------------

// Tree: add command test
TEST(TreeTest, addTest) {
    Tree myTree;
    myTree.root = myTree.add(myTree.root, 5);
    myTree.root = myTree.add(myTree.root, 3);
    myTree.root = myTree.add(myTree.root, 7);

    ASSERT_EQ(myTree.root->key, 5);
    ASSERT_EQ(myTree.root->left->key, 3);
    ASSERT_EQ(myTree.root->right->key, 7);
}

// Tree: search command test
TEST(TreeTest, searchTest) {
    Tree myTree;
    myTree.root = myTree.add(myTree.root, 5);
    myTree.root = myTree.add(myTree.root, 3);
    myTree.root = myTree.add(myTree.root, 7);

    TreeNode *result1 = myTree.search(myTree.root, 5);
    TreeNode *result2 = myTree.search(myTree.root, 3);
    TreeNode *result3 = myTree.search(myTree.root, 7);
    TreeNode *result4 = myTree.search(myTree.root, 10);

    ASSERT_NE(result1, nullptr);
    ASSERT_EQ(result1->key, 5);

    ASSERT_NE(result2, nullptr);
    ASSERT_EQ(result2->key, 3);

    ASSERT_NE(result3, nullptr);
    ASSERT_EQ(result3->key, 7);

    ASSERT_EQ(result4, nullptr);
}

// Tree: search command test - not found
TEST(TreeTest, searchTestNotFound) {
    Tree myTree;

    TreeNode *result1 = myTree.search(myTree.root, 5);

    ASSERT_EQ(result1, nullptr);
}

// Tree: succ command test
TEST(TreeTest, succTest) {
    Tree myTree;
    myTree.root = myTree.add(myTree.root, 5);
    myTree.root = myTree.add(myTree.root, 3);
    myTree.root = myTree.add(myTree.root, 7);

    TreeNode *successor1 = myTree.succ(myTree.root->left);

    ASSERT_EQ(successor1, myTree.root);
}

// Tree: min command test
TEST(TreeTest, minTest) {
    Tree myTree;
    myTree.root = myTree.add(myTree.root, 5);
    myTree.root = myTree.add(myTree.root, 3);
    myTree.root = myTree.add(myTree.root, 7);

    TreeNode *minNode = myTree.min(myTree.root);

    ASSERT_EQ(minNode->key, 3);
}

// Tree: print command test
TEST(TreeTest, printTest) {
    Tree myTree;
    myTree.root = myTree.add(myTree.root, 5);
    myTree.root = myTree.add(myTree.root, 3);
    myTree.root = myTree.add(myTree.root, 7);

    // Redirect cout to a stringstream for testing
    testing::internal::CaptureStdout();
    myTree.print(myTree.root, 0);
    string output = testing::internal::GetCapturedStdout();

    string expectedOutput = "\n    7\n\n5\n\n    3\n";

    ASSERT_EQ(output, expectedOutput);
}

// Tree: del command test
TEST(TreeTest, delTest) {
    Tree myTree;
    myTree.root = myTree.add(myTree.root, 5);
    myTree.root = myTree.add(myTree.root, 3);
    myTree.root = myTree.add(myTree.root, 7);
    myTree.root = myTree.add(myTree.root, 1);
    myTree.root = myTree.add(myTree.root, 2);

    myTree.root = myTree.del(myTree.root, 7);

    ASSERT_EQ(myTree.root->key, 5);
}

// ---------------------------------------------------------------

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
