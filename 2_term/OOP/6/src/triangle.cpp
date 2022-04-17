#include "triangle.h"

#include <cmath>
#include <stdexcept>

#include "triangleangles.h"
#include "trianglesides.h"

bool compare_double(double x, double y, double epsilon = 0.01) {
  return fabs(x - y) < epsilon;
}

Triangle::Triangle() { Triangle::incrementTrianglesCount(); }

Triangle::Triangle(TriangleSides sides) {
  if (!this->isValid(sides)) {
    throw std::invalid_argument("Received triangle cannot exist");
  }
  Triangle::incrementTrianglesCount();

  this->setSides(sides);
}

bool Triangle::isValid(TriangleSides sides) {
  auto biggestSide = std::max({sides.a, sides.b, sides.c});
  auto shortenedSum = sides.a + sides.b + sides.c - biggestSide;

  return shortenedSum > biggestSide;
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
  auto area = this->getArea();

  TriangleHeights heights;
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

TriangleSides Triangle::increaseSidesTimes(const double by) {
  this->sides.a *= by;
  this->sides.c *= by;
  this->sides.b *= by;

  return this->sides;
}

Triangle *Triangle::operator+(const double increaseSidesBy) {
  this->increaseSidesBy(increaseSidesBy);

  return this;
}

Triangle *Triangle::operator*(const double increaseSidesTimes) {
  this->increaseSidesTimes(increaseSidesTimes);

  return this;
}

double Triangle::operator[](const int i) { return *this->sidesArr[i]; }

Triangle::operator double() { return this->getArea(); }

void operator<<(QLineEdit *out[TRIANGLE_SIDES_COUNT], Triangle &triangle) {
  out[0]->setText(QString::number(triangle.sides.a));
  out[1]->setText(QString::number(triangle.sides.b));
  out[2]->setText(QString::number(triangle.sides.c));
};

void operator>>(QLineEdit *in[TRIANGLE_SIDES_COUNT], Triangle &triangle) {
  TriangleSides sides = triangle.getSides();
  sides.a = in[0]->text().toDouble();
  sides.b = in[1]->text().toDouble();
  sides.c = in[2]->text().toDouble();
  triangle.setSides(sides);
};

bool operator>(Triangle &tr1, Triangle &tr2) {
  return tr1.getArea() > tr2.getArea();
};

bool operator<(Triangle &tr1, Triangle &tr2) {
  return tr1.getArea() < tr2.getArea();
};

bool operator==(Triangle &tr1, Triangle &tr2) {
  return compare_double(tr1.getArea(), tr2.getArea());
};
