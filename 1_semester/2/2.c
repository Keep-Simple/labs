#include <stdio.h>
#include <math.h>

// завдання 5 з додатку 1
int *findTwoDigitNumbers(int *arrayLength)
{
	static int resultNums[90];
	int i = 0;

	for (int n = 10; n < 100; n++)
	{
		int firstDigit = n / 10;
		int secondDigit = n % 10;

		if ((firstDigit + secondDigit) * 2 == n)
		{
			resultNums[i++] = n;
		}
	}

	*arrayLength = i;

	return resultNums;
}

// завдання 4 з додатку 2
typedef double (*doubleMathFunc)(double);

void checkTaylorFunctionPrecision(
	int xLowExclusive, int xHighInclusive,
	doubleMathFunc tayloarFunc,
	doubleMathFunc initalFunc)
{
	double step, start, end;

	printf("Enter: step, start, end (to define xAsix iteration):");
	scanf("%lf %lf %lf", &step, &start, &end);

	if (start <= xLowExclusive || xHighInclusive < end || start > end || step > fabs(start - end))
	{
		printf("Error: user input does't match bounds (%d, %d] or step is to big.\n",
			   xLowExclusive, xHighInclusive);

		return;
	}

	while (start < end)
	{
		printf("|\tx = %lf\t|\t", start);
		printf("formula result = %lf\t|\t", initalFunc(start));
		printf("taylor result = %lf\t|\n", tayloarFunc(start));
		printf("---------------------------------------------------------------------------------------------------------\n");
		start += step;
	}
}

double lnFormula(double x)
{
	return log(1 + x);
}

double taylorLn(double x)
{
	double prevElement = x, result = x, eps = 1E-200;
	long idx = 2;

	while (fabs(prevElement) >= eps)
	{
		prevElement = prevElement * x / idx;
		result += prevElement * pow(-1, idx + 1);
		idx++;
	}

	return result;
}

int main()
{
	printf("Task 5 from 1st section\n");
	int SIZE = 0;
	int *resultNums = findTwoDigitNumbers(&SIZE);

	for (int i = 0; i < SIZE; i++)
	{
		printf("Number: %d with idx: %d\n", resultNums[i], i);
	}

	printf("\n\nTask 4 from 2nd section\n");

	checkTaylorFunctionPrecision(-1, 1, lnFormula, taylorLn);

	return 0;
}
