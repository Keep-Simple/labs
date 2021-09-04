#include <stdio.h>
#include <math.h>

// завдання 5 з додатку 1
double firstCalcTask(int x, int a, int p, int b)
{
    return (x / a) - log2(a + b * exp(p * x)) / (a * p);
}

int getNthDigit(int number, int digitIdx)
{
    return number / (int)pow(10, digitIdx - 1) % 10;
}

int main()
{
    printf("Task 5 from 1st section\n");
    printf("Result: %lf\n\n", firstCalcTask(2, 3, 6, 2));

    return 0;
}