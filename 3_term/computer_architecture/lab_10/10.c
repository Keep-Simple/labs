#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  float a = 7.3;
  float c = 6.3;
  float d = 5.4;
  float res;

  if (d >= a * c) {
    res = 5.8 * c - sqrt(9.9 + 17 * d) - c * a;
  } else {
    res = sqrt(fabs(9.8 * a - c / 4.3 + 8.4 * d));
  }

  printf("%f\n", res);
}
