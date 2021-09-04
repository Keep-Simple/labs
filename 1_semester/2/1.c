#include <stdio.h>
#include <math.h>

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

int main()
{
	printf("Task 5 from 1st section\n");
	int SIZE = 0;
	int *resultNums = findTwoDigitNumbers(&SIZE);

	for (int i = 0; i < SIZE; i++)
	{
		printf("Number: %d with idx: %d\n", resultNums[i], i);
	}

	return 0;
}
