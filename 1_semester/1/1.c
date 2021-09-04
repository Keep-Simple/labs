#include <stdio.h>
#include <math.h>

// завдання 5 з додатку 1
double firstCalcTask(const int x, const int a, const int p, const int b)
{
	return (x / a) - log2(a + b * exp(p * x)) / (a * p);
}

int getNthDigit(const int number, const int digitIdx)
{
	return number / (int)pow(10, digitIdx - 1) % 10;
}

// завдання 7 з додатку 2
// find 9-digit positive integer's figures sum and "1" count
// loops are forbidden
void secondCalcTask(const int nineDigitNum, int *const figuresSum, int *const oneCount)
{
	if (nineDigitNum >= pow(10, 9) || nineDigitNum < pow(10, 8))
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

int main()
{
	printf("Task 5 from 1st section\n");
	printf("Result: %lf\n\n", firstCalcTask(2, 3, 6, 2));

	printf("Task 7 from 2nd section\n");

	const int INPUT_9_DIGIT_NUMBER = 111333888;
	int figuresSum = 0, oneCount = 0;
	secondCalcTask(INPUT_9_DIGIT_NUMBER, &figuresSum, &oneCount);

	printf("Figures sum: %d\n'1' count: %d\n", figuresSum, oneCount);

	return 0;
}
