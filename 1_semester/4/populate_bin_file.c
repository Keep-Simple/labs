#include <stdio.h>

int main()
{
	double x;
	printf("Enter x: ");
	scanf("%lf", &x);

	FILE *file = fopen("input.bin", "wb");
	fwrite(&x, sizeof(x), 1, file);

	fclose(file);
	return 0;
}