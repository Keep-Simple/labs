#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES

typedef struct tabulatedRes
{
    double x;
    double value;
} tabulatedRes;
typedef double doubleMathFunc(double);
typedef void getResultsFunc(double, double, double, doubleMathFunc *, tabulatedRes *);

double mathFunc(double x)
{
    return pow(cos(4 * x), 2);
}
void getResultsWithFor(double start, double end, double step, doubleMathFunc *func, tabulatedRes *results)
{
    int length = (end - start) / step;

    for (int i = 0; i < length; i++, start += step)
    {
        results[i].x = start;
        results[i].value = func(start);
    }
}
void getResultsWithWhile(double start, double end, double step, doubleMathFunc *func, tabulatedRes *results)
{
    while (start < end)
    {
        *results++;
        results->x = start;
        results->value = func(start);
        start += step;
    }
}
void getResultsWithDoWhile(double start, double end, double step, doubleMathFunc *func, tabulatedRes *results)
{
    do
    {
        *results++;
        results->x = start;
        results->value = func(start);
        start += step;

    } while (start < end);
}

void printTabulateResults(double start, double end, double step, doubleMathFunc *func, int option)
{
    int length = (end - start) / step;
    tabulatedRes *results = (tabulatedRes *)malloc(length * sizeof(tabulatedRes));

    getResultsFunc *getResult;

    switch (option)
    {
    case 1:
        getResult = &getResultsWithFor;
        break;
    case 2:
        getResult = &getResultsWithWhile;
        break;
    case 3:
        getResult = &getResultsWithDoWhile;
        break;
    default:
        break;
    }

    getResultsWithFor(start, end, step, func, results);

    printf("Printing tabulated results:\n");
    for (int i = 0; i < length; i++)
    {
        printf("x=%lf\ty=%lf\n", results[i].x, results[i].value);
    }

    free(results);
}

int main(void)
{
    printf("Task 3, Section 2:\n");

    const double start = -M_PI / 2, end = 0;
    double step;
    int option;
    printf("Enter step: ");
    scanf("%lf", &step);

    printf("Enter option number [1/2/3]: ");
    scanf("%d", &option);

    printTabulateResults(start, end, step, &mathFunc, option);

    return 0;
}
