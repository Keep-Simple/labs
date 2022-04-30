#import "node.h"

// A structure to represent a deque
class Deque {
protected:
  Node *front;
  Node *rear;
  int size;

public:
  Deque() {
    front = rear = NULL;
    size = 0;
  }

  // Copy contructor
  Deque(const Deque &dq) {
    this->front = dq.front;
    this->rear = dq.rear;
  }

  ~Deque() { this->erase(); }

  // Operations on Deque
  void insertFront(int data);
  void insertRear(int data);
  void deleteFront();
  void deleteRear();
  Node *getFront();
  Node *getRear();
  double getSize();
  bool isEmpty();
  void erase();
};
