#include <math.h>
#include <stdio.h>

int main() {
  double a = 4.3, c = 7, d = 1.2;
  double res =
      (4 / a - cos(c * a) + sqrt(23 * c - 4)) / (8.4 * c - d / 9 + 13 * a);
  printf("Result=%f\n\n\n", res);
  return 0;
}
