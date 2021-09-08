#include <stdio.h>
#include <math.h>

void findTwoDigitNumbers(int *resultNums, int *arrayLength)
{
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
}

int main(void)
{
	printf("Task 5 from 1st section\n");
	int SIZE = 0;
	int resultNums[90];
	findTwoDigitNumbers(resultNums, &SIZE);

	for (int i = 0; i < SIZE; i++)
	{
		printf("Number: %d with idx: %d\n", resultNums[i], i);
	}

	return 0;
}
