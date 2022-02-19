#include <stdio.h>
#include <math.h>

double _numberOfTaylor(double x, double precision, int step, double sum, double prevElement)
{
    double currentElement = (prevElement * x) / ++step;
    if (precision >= fabs(currentElement))
    {
        return sum;
    }
    return _numberOfTaylor(x, precision, step, sum + currentElement, currentElement);
}

double numberOfTaylor(double x, double precision)
{
    return _numberOfTaylor(x, precision, 0, 0, 1);
}

int main(void)
{
    double x, eps;

    printf("Enter x: ");
    scanf("%lf", &x);
    printf("Enter eps: ");
    scanf("%lf", &eps);

    double result = numberOfTaylor(x, eps);

    printf("Result = %lf\n", result);

    return 0;
}
