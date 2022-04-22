#pragma once

#include <QLineEdit>
#include <map>

#define POLYNOM_LENGTH 3

class Polynom {
 private:
  static inline int polynomsCount = 0;

  double a, b, c;
  double *coff[POLYNOM_LENGTH] = {&this->a, &this->b, &this->c};

 public:
  Polynom();
  ~Polynom();
  Polynom(double a, double b, double c);

  static int getPolynomsCount() { return Polynom::polynomsCount; };
  static void incrementPolynomsCount() { Polynom::polynomsCount++; };
  static void decrementPolynomsCount() { Polynom::polynomsCount--; };

  auto getCoff() { return this->coff; };

  Polynom *operator+(const Polynom addPolynom);
  Polynom *operator-(const Polynom substractPolynom);
  Polynom *operator*(const double increaseBy);
  Polynom *operator!();
  double operator()(double x);

  friend void operator<<(QLineEdit *out[POLYNOM_LENGTH], Polynom &triangle);
  friend void operator>>(QLineEdit *in[POLYNOM_LENGTH], Polynom &triangle);
  friend bool operator==(Polynom &tr1, Polynom &tr2);
};
