#include "deque.h"
#include <stdexcept>

// Function to check whether deque
// is empty or not
bool Deque::isEmpty() { return (front == NULL); }

// Function to return the number of
// elements in the deque
double Deque::getSize() { return size; }

// Function to insert an element
// at the front end
void Deque::insertFront(int data) {
  Node *newNode = Node::getNode(data);
  // If true then new element cannot be added
  // and it is an 'Overflow' condition
  if (newNode == NULL)
    throw std::invalid_argument("overflow");
  else {
    // If deque is empty
    if (front == NULL)
      rear = front = newNode;

    // Inserts node at the front end
    else {
      newNode->next = front;
      front->prev = newNode;
      front = newNode;
    }

    // Increments count of elements by 1
    size++;
  }
}

// Function to insert an element
// at the rear end
void Deque::insertRear(int data) {
  Node *newNode = Node::getNode(data);
  // If true then new element cannot be added
  // and it is an 'Overflow' condition
  if (newNode == NULL)
    throw std::invalid_argument("overflow");
  else {
    // If deque is empty
    if (rear == NULL)
      front = rear = newNode;

    // Inserts node at the rear end
    else {
      newNode->prev = rear;
      rear->next = newNode;
      rear = newNode;
    }

    size++;
  }
}

// Function to delete the element
// from the front end
void Deque::deleteFront() {
  // If deque is empty then
  // 'Underflow' condition
  if (isEmpty())
    throw std::invalid_argument("underflow");

  // Deletes the node from the front end and makes
  // the adjustment in the links
  else {
    Node *temp = front;
    front = front->next;

    // If only one element was present
    if (front == NULL)
      rear = NULL;
    else
      front->prev = NULL;
    free(temp);

    // Decrements count of elements by 1
    size--;
  }
}

// Function to delete the element
// from the rear end
void Deque::deleteRear() {
  // If deque is empty then
  // 'Underflow' condition
  if (isEmpty())
    throw std::invalid_argument("underflow");

  // Deletes the node from the rear end and makes
  // the adjustment in the links
  else {
    Node *temp = rear;
    rear = rear->prev;

    // If only one element was present
    if (rear == NULL)
      front = NULL;
    else
      rear->next = NULL;
    free(temp);

    // Decrements count of elements by 1
    size--;
  }
}

Node *Deque::getFront() { return this->front; }

Node *Deque::getRear() { return this->rear; }

// Function to delete all the elements
// from Deque
void Deque::erase() {
  rear = NULL;
  while (front != NULL) {
    Node *temp = front;
    front = front->next;
    free(temp);
  }
  size = 0;
}
