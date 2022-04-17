#pragma once

#include "triangleangles.h"
#include "triangleheights.h"
#include "trianglesides.h"

class Triangle {
 private:
  TriangleSides sides;
  bool isValid(TriangleSides sides);

 public:
  auto getSides() { return this->sides; }
  void setSides(TriangleSides sides) { this->sides = sides; };

  Triangle(TriangleSides sides);

  bool isRectangular();
  double getArea();
  double getPerimeter();
  TriangleAngles getAngles();
  TriangleHeights getHeights();
  TriangleSides increaseSidesBy(const double by);
};
