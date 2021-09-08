#include <stdio.h>
#include <math.h>

const double a = 3, p = 6, b = 2;

double firstCalcTask(double x)
{
    // add validation
    return (x / a) - log(a + b * exp(p * x)) / (a * p);
}
