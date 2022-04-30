#include <stdlib.h> /* malloc, free, rand */

// Node of a doubly linked list
struct Node {
  double data;
  Node *prev, *next;
  // Function to get a new node
  static Node *getNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
  }
};
