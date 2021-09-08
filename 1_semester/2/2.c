#include <stdio.h>
#include <math.h>

typedef double doubleMathFunc(double);

void checkTaylorFunctionPrecision(
	int xLowExclusive, int xHighInclusive,
	doubleMathFunc tayloarFunc,
	doubleMathFunc initalFunc)
{
	double step, start, end;

	printf("Enter: step, start, end (to define xAsix iteration): ");
	scanf("%lf %lf %lf", &step, &start, &end);

	if (start <= xLowExclusive || xHighInclusive < end || start > end || step > fabs(start - end) || step == 0)
	{
		printf("Error: user input does't match bounds (%d, %d] or step value is invalid.\n",
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

	while (fabs(prevElement) > eps)
	{
		prevElement *= x / idx * (idx - 1);

		if (idx++ % 2 == 0)
			result -= prevElement;
		else
			result += prevElement;
	}

	return result;
}

int main()
{
	printf("\n\nTask 4 from 2nd section\n");

	checkTaylorFunctionPrecision(-1, 1, lnFormula, taylorLn);

	return 0;
}
