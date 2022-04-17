#include <iostream>
#define COEF_LEN 100

using namespace std;

class Polynomial {
  int coef[COEF_LEN];
  // coef[0] would hold all coefficients of x^0
  // coef[n] = x^n ...
  int deg;

 public:
  Polynomial() {
    for (int i = 0; i < COEF_LEN; i++) {
      coef[i] = 0;
    }
  }

  void set(int a, int b) {
    coef[b] = a;
    deg = degree();
  }

  int degree() {
    int d = 0;
    for (int i = 0; i < COEF_LEN; i++)
      if (coef[i] != 0) d = i;
    return d;
  }

  void print() {
    for (int i = COEF_LEN - 1; i >= 0; i--) {
      if (coef[i] != 0) {
        cout << coef[i] << "x^" << i << " ";
      }
    }
  }

  int evaluate(int x) {
    int p = 0;
    for (int i = deg; i >= 0; i--) p = coef[i] + (x * p);
    return p;
  }

  void find_roots() {}

  void calc_integral() {}

  Polynomial differentiate() {
    if (deg == 0) {
      Polynomial t;
      t.set(0, 0);
      return t;
    }
    Polynomial deriv;  // = new Polynomial ( 0, deg - 1 );
    deriv.deg = deg - 1;
    for (int i = 0; i < deg; i++) deriv.coef[i] = (i + 1) * coef[i + 1];
    return deriv;
  }

  Polynomial plus(Polynomial b) {
    Polynomial a = *this;
    Polynomial c;

    for (int i = 0; i <= a.deg; i++) c.coef[i] += a.coef[i];
    for (int i = 0; i <= b.deg; i++) c.coef[i] += b.coef[i];
    c.deg = c.degree();

    return c;
  }

  Polynomial minus(Polynomial b) {
    Polynomial a = *this;
    Polynomial c;

    for (int i = 0; i <= a.deg; i++) c.coef[i] += a.coef[i];
    for (int i = 0; i <= b.deg; i++) c.coef[i] -= b.coef[i];
    c.deg = c.degree();

    return c;
  }

  Polynomial times(Polynomial b) {
    Polynomial a = *this;
    Polynomial c;

    for (int i = 0; i <= a.deg; i++)
      for (int j = 0; j <= b.deg; j++) c.coef[i + j] += (a.coef[i] * b.coef[j]);
    c.deg = c.degree();
    return c;
  }
};

int main() {
  Polynomial a, b, c, d;
  a.set(7, 4);  // 7x^4
  a.set(1, 2);  // x^2

  b.set(6, 3);   // 6x^3
  b.set(-3, 2);  //-3x^2

  c = a.minus(b);  // (7x^4 + x^2) - (6x^3 - 3x^2)

  c.print();

  cout << "\n";

  c = a.times(b);  // (7x^4 + x^2) * (6x^3 - 3x^2)
  c.print();

  cout << "\n";

  d = c.differentiate().differentiate();
  d.print();

  cout << "\n";

  cout << c.evaluate(2);  // substitue x with 2

  cin.get();
}
