#include "polynom.h"

#include <cmath>
#include <stdexcept>

bool compare_double(double x, double y, double epsilon = 0.01) {
  return fabs(x - y) < epsilon;
}

Polynom::Polynom() {
  a = b = c = 0;
  Polynom::incrementPolynomsCount();
}

Polynom::Polynom(double a, double b, double c) {
  Polynom::incrementPolynomsCount();
  this->a = a;
  this->b = b;
  this->c = c;
}

Polynom::~Polynom() { Polynom::decrementPolynomsCount(); }

Polynom *Polynom::operator*(const double increaseBy) {
  if (increaseBy != 0) {
    this->a *= increaseBy;
    this->b *= increaseBy;
    this->c *= increaseBy;
  }
  return this;
}

Polynom *Polynom::operator-(Polynom substractPolynom) {
  this->a -= substractPolynom.a;
  this->b -= substractPolynom.b;
  this->c -= substractPolynom.c;
  return this;
}

Polynom *Polynom::operator!() {
  this->a = -this->a;
  this->b = -this->b;
  this->c = -this->c;
  return this;
}

Polynom *Polynom::operator+(Polynom addPolynom) {
  this->a += addPolynom.a;
  this->b += addPolynom.b;
  this->c += addPolynom.c;
  return this;
}

double Polynom::operator()(double x) { return a * (pow(x, 2)) + b * x + c; }

void operator<<(QLineEdit *out[POLYNOM_LENGTH], Polynom &polynom) {
  out[0]->setText(QString::number(polynom.a));
  out[1]->setText(QString::number(polynom.b));
  out[2]->setText(QString::number(polynom.c));
};

void operator>>(QLineEdit *in[POLYNOM_LENGTH], Polynom &polynom) {
  polynom.a = in[0]->text().toDouble();
  polynom.b = in[1]->text().toDouble();
  polynom.c = in[2]->text().toDouble();
};

bool operator==(Polynom &p1, Polynom &p2) {
  return compare_double(p1.a, p2.a) || compare_double(p1.b, p2.b) ||
         compare_double(p1.c, p2.c);
};
