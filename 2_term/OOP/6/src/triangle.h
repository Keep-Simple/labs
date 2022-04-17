#pragma once

#include <QLineEdit>
#include <map>

#include "triangleangles.h"
#include "triangleheights.h"
#include "trianglesides.h"

#define TRIANGLE_SIDES_COUNT 3

class Triangle {
 private:
  TriangleSides sides;
  static inline int trianglesCount = 0;
  double *sidesArr[TRIANGLE_SIDES_COUNT] = {&this->sides.a, &this->sides.b,
                                            &this->sides.c};

  bool isValid(TriangleSides sides);

 public:
  Triangle(TriangleSides sides);
  Triangle();

  static int getTrianglesCount() { return Triangle::trianglesCount; };
  static void incrementTrianglesCount() { Triangle::trianglesCount++; };

  auto getSides() { return this->sides; };
  void setSides(TriangleSides sides) { this->sides = sides; };

  Triangle *operator+(const double increaseSidesBy);
  Triangle *operator*(const double increaseSidesTimes);

  double operator[](const int i);
  operator double();

  friend void operator<<(QLineEdit *out[TRIANGLE_SIDES_COUNT],
                         Triangle &triangle);
  friend void operator>>(QLineEdit *in[TRIANGLE_SIDES_COUNT],
                         Triangle &triangle);

  friend bool operator>(Triangle &tr1, Triangle &tr2);
  friend bool operator<(Triangle &tr1, Triangle &tr2);
  friend bool operator==(Triangle &tr1, Triangle &tr2);

  bool isRight();
  double getArea();
  double getPerimeter();
  TriangleAngles getAngles();
  TriangleHeights getHeights();
  TriangleSides increaseSidesBy(const double by);
  TriangleSides increaseSidesTimes(const double by);
};
