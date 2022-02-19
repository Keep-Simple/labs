#include <stdio.h>
#include <math.h>

int intPow(int x, int y)
{
    // adding 0.5 so all compilers would round number properly
    return (int)(pow(x, y) + 0.5);
}

// find 9-digit positive integer's figures sum and "1" count
// loops are forbidden
void secondCalcTask(int nineDigitNum, int *const figuresSum, int *const oneCount)
{
    if (nineDigitNum >= intPow(10, 9) || nineDigitNum < intPow(10, 8))
    {
        printf("Error: Input number should be positive and 9-digit\n\n");
        return;
    }

    *figuresSum = getNthDigit(nineDigitNum, 9) + getNthDigit(nineDigitNum, 8) + getNthDigit(nineDigitNum, 7) +
                  getNthDigit(nineDigitNum, 6) + getNthDigit(nineDigitNum, 5) + getNthDigit(nineDigitNum, 4) +
                  getNthDigit(nineDigitNum, 3) + getNthDigit(nineDigitNum, 2) + getNthDigit(nineDigitNum, 1);

    *oneCount = (getNthDigit(nineDigitNum, 9) == 1) + (getNthDigit(nineDigitNum, 8) == 1) + (getNthDigit(nineDigitNum, 7) == 1) +
                (getNthDigit(nineDigitNum, 6) == 1) + (getNthDigit(nineDigitNum, 5) == 1) + (getNthDigit(nineDigitNum, 4) == 1) +
                (getNthDigit(nineDigitNum, 3) == 1) + (getNthDigit(nineDigitNum, 2) == 1) + (getNthDigit(nineDigitNum, 1) == 1);
}

int getNthDigit(int number, int digitIdx)
{
    return number / intPow(10, digitIdx - 1) % 10;
}

int main(void)
{
    printf("Task 7 from 2nd section\n");

    int INPUT_9_DIGIT_NUMBER;
    printf("Enter 9-digit num: ");
    scanf("%d", &INPUT_9_DIGIT_NUMBER);

    int figuresSum = 0, oneCount = 0;

    secondCalcTask(INPUT_9_DIGIT_NUMBER, &figuresSum, &oneCount);

    printf("Figures sum: %d\n'1' count: %d\n", figuresSum, oneCount);

    return 0;
}
