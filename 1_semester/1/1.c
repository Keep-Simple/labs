#include <stdio.h>
#include <math.h>

const double a = 3, p = 6, b = 2;

double firstCalcTask(double x)
{
    double dangerousCalc = a + b * exp(p * x);

    if (dangerousCalc <= 0 || a == 0 || p == 0)
    {
        printf("Error: Invalid input arguments!");
        return -1;
    }
    return (x / a) - log(dangerousCalc) / (a * p);
}
