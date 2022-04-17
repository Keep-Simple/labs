#include "triangle.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include "triangleangles.h"
#include "trianglesides.h"

bool compare_double(double x, double y, double epsilon = 0.01) {
  return fabs(x - y) < epsilon;
}

bool Triangle::isValid(TriangleSides sides) {
  auto biggestSide = std::max({sides.a, sides.b, sides.c});
  auto shortenedSum = sides.a + sides.b + sides.c - biggestSide;
  return shortenedSum > biggestSide;
}

Triangle::Triangle(TriangleSides sides) {
  if (!this->isValid(sides)) {
    throw std::invalid_argument("Received triangle cannot exist");
  }
  this->setSides(sides);
}

bool Triangle::isRight() {
  return compare_double(pow(this->sides.c, 2),
                        pow(this->sides.a, 2) + pow(this->sides.b, 2));
};

double Triangle::getPerimeter() {
  return this->sides.a + this->sides.b + this->sides.c;
}

double Triangle::getArea() {
  auto p = this->getPerimeter() / 2;
  return sqrt(p * (p - this->sides.a) * (p - this->sides.b) *
              (p - this->sides.c));
}

TriangleAngles Triangle::getAngles() {
  auto calcAngle = [](double a, double b, double c) {
    return (180. / M_PI) *
           acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a * b));
  };

  TriangleAngles angles;
  angles.cab = calcAngle(this->sides.a, this->sides.b, this->sides.c);
  angles.abc = calcAngle(this->sides.a, this->sides.c, this->sides.b);
  angles.bca = calcAngle(this->sides.b, this->sides.c, this->sides.a);

  return angles;
}

TriangleHeights Triangle::getHeights() {
  TriangleHeights heights;

  auto area = this->getArea();

  heights.ak = (2 * area) / this->sides.a;
  heights.bk = (2 * area) / this->sides.b;
  heights.ck = (2 * area) / this->sides.c;

  return heights;
}

TriangleSides Triangle::increaseSidesBy(const double by) {
  this->sides.a += by;
  this->sides.c += by;
  this->sides.b += by;

  return this->sides;
}
