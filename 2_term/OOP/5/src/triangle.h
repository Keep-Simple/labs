#pragma once

class TriangleAngles {
 public:
  double abc;
  double bca;
  double cab;
};

class TriangleHeights {
 public:
  double ak;
  double bk;
  double ck;
};

class TriangleSides {
 public:
  double a;
  double b;
  double c;
};

class Triangle {
 private:
  TriangleSides sides;
  bool isValid(TriangleSides sides);

 public:
  auto getSides() { return this->sides; }
  void setSides(TriangleSides sides) { this->sides = sides; };

  Triangle(TriangleSides sides);

  bool isRight();
  double getArea();
  double getPerimeter();
  TriangleAngles getAngles();
  TriangleHeights getHeights();
  TriangleSides increaseSidesBy(const double by);
};
