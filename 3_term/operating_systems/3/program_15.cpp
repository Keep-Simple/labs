#include <string>
#include <iostream>
#include <cmath>

void tabulate_lnx(double a, double b, double step, double iter_count) {
  for (double n = a; n <= b; n += step) {
    double num, mul, cal, sum = 0;
    num = (n - 1) / (n + 1);

    // terminating value of the loop
    // can be increased to improve the precision
    for (int i = 1; i <= iter_count; i++) {
      mul = (2 * i) - 1;
      cal = pow(num, mul);
      cal = cal / mul;
      sum = sum + cal;
    }
    sum = 2 * sum;
    std::cout << "ln(" << n << ")=" << sum << std::endl;
  }
}

int main(int argc, char **argv) {
  if (argc != 5)
    return 1;
  double a = atof(argv[1]);
  double b = atof(argv[2]);
  double step = atof(argv[3]);
  int iter_count = atoi(argv[4]);
  std::cout << "a: " << a << " b " << b << " step " << step << " "
            << " iter count" << iter_count << std::endl;
  tabulate_lnx(a, b, step, iter_count);
}
