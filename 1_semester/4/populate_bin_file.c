#include <stdio.h>

int main()
{
	int x;
	printf("Enter x: ");
	scanf("%d", &x);

	FILE *file = fopen("input.bin", "wb");
	fwrite(&x, sizeof(x), 1, file);

	fclose(file);
	return 0;
}