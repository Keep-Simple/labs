#include <cmath>
#include <iostream>
#include <string>

void tabulate_lnx(double a, double b, double step, double iter_count) {
  for (double n = a; n <= b; n += step) {
    double num, m, c, sum = 0;
    num = (n - 1) / (n + 1);

    for (auto i = 0; i < iter_count; i++) {
      m = (2 * i) - 1;
      c = pow(num, m);
      c = c / m;
      sum = sum + c;
    }

    sum = 2 * sum;
    std::cout << "ln(" << n << ") = " << sum << std::endl;
  }
}

int main(int argc, char **argv) {
  if (argc != 5) {
    return 1;
  }
  double a = atof(argv[1]);
  double b = atof(argv[2]);
  double step = atof(argv[3]);
  int iterations = atoi(argv[4]);

  std::cout << "a: " << a << " b " << b << " step " << step << " "
            << " iter count" << iterations << std::endl;

  tabulate_lnx(a, b, step, iterations);
}
