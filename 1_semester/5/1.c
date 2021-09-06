#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES

const double a = -M_PI / 2, b = 0;

double performCalculation(double x)
{
    return pow(cos(4 * x), 2);
}

void performCalcReturnByPointer(double x, double *result)
{
    double res = performCalculation(x);

    if (res < 0)
    {
        *result = -1;
        return;
    }

    if (res > 0)
    {
        *result = 1;
        return;
    }

    if (res == 0)
    {
        *result = 0;
        return;
    }
}

void displayFuncResult(double x, double y)
{
    printf("|\tx = %.3lf\t|\ty = %.3lf\t|\n-------------------------------------------------\n", x, y);
}

int main()
{
    printf("Task 3\n");

    double step;
    int variant;
    printf("Enter step: ");
    scanf("%lf", &step);

    while (variant != 1 && variant != 2)
    {
        printf("Pick variant [1/2]: ");
        scanf("%d", &variant);
    }

    double cursor = a, end = b;

    while (cursor < end)
    {
        double result;
        if (variant == 1)
        {
            result = performCalculation(cursor);
        }
        if (variant == 2)
        {
            performCalcReturnByPointer(cursor, &result);
        }
        displayFuncResult(cursor, result);
        cursor += step;
    }

    return 0;
}