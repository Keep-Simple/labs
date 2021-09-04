#include <stdio.h>
#include <math.h>

const int a = 3, p = 6, b = 2;

double firstCalcTask(int x)
{
    return (x / a) - log2(a + b * exp(p * x)) / (a * p);
}
