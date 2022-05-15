#ifndef __ARRAY_CPP
#define __ARRAY_CPP

#include "array.h"

template <typename T>
std::string ArrayInfoPrinter<T>::get_info_abstract() const {
  return "General Info";
};

template <typename T>
std::string ArrayInfoPrinter<T>::get_info() const {
  return "Simple info";
};

template <typename T>
int BasicArray<T>::length() const {
  return this->elements.size();
}

template <typename T>
bool BasicArray<T>::includes(T const val) const {
  for (T i : this->elements) {
    if (i == val) {
      return true;
    }
  }
  return false;
}

template <typename T>
void BasicArray<T>::push(T const& val) {
  this->elements.push_back(val);
}

template <typename T>
std::string BasicArray<T>::get_info_abstract() const {
  return ArrayInfoPrinter<T>::get_info_abstract() + " from BasicArray";
}

template <typename T>
SinglyLinkedArray<T>::SinglyLinkedArray() : head(nullptr) {}

template <typename T>
SinglyLinkedArray<T>::~SinglyLinkedArray() {
  Node* i = this->head;
  while (i != nullptr) {
    i = i->next;
    delete i;
    delete i->data;
  }
}

template <typename T>
int SinglyLinkedArray<T>::length() const {
  int count = 0;
  for (auto i = this->head; i != nullptr; i = i->next) {
    count++;
  }
  return count;
}

template <typename T>
void SinglyLinkedArray<T>::push(T const& val) {
  auto newNode = new Node(val);

  if (head == nullptr) {
    head = newNode;
    return;
  }

  auto i = head;
  while (i->next != nullptr) i = i->next;
  i->next = newNode;
}

template <typename T>
bool SinglyLinkedArray<T>::includes(T const val) const {
  auto i = head;
  while (i != nullptr) {
    if (i->data == val) return true;
  }
  return false;
}

template <typename T>
std::string SinglyLinkedArray<T>::get_info_abstract() const {
  return ArrayInfoPrinter<T>::get_info_abstract() + " from SinglyLinkedArray";
}

#endif
