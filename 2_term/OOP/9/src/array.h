#ifndef __ARRAY_H
#define __ARRAY_H

#include <string>
#include <vector>

template <typename T>
class ArrayInfoPrinter {
 public:
  std::string get_info() const;
  virtual std::string get_info_abstract() const = 0;
};

template <typename T>
class Array : public virtual ArrayInfoPrinter<T> {
 public:
  virtual int length() const = 0;
  virtual bool includes(T const) const = 0;
  virtual void push(T const &) = 0;
};

template <typename T>
class Array2 : public virtual ArrayInfoPrinter<T> {};

template <typename T>
class BasicArray : public Array<T>, public Array2<T> {
 private:
  std::vector<T> elements;

 public:
  int length() const override;
  bool includes(T const) const override;
  void push(T const &) override;

  std::string get_info_abstract() const override;
};

template <typename T>
class SinglyLinkedArray : public Array<T>, public Array2<T> {
 private:
  class Node {
   public:
    T data;
    Node *next;
    Node() : next(nullptr) {}
    Node(T data) : data(data), next(nullptr) {}
  };

  Node *head;

 public:
  SinglyLinkedArray();
  ~SinglyLinkedArray();

  int length() const override;
  bool includes(T const) const override;
  void push(T const &) override;

  std::string get_info_abstract() const override;
};

#include "array.cpp"

#endif
