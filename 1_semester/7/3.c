#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    printf("Task 6, Section 3:\n");

    char strNumber[300];
    int number[300];
    printf("Enter number: ");
    scanf("%s", strNumber);

    int length = strlen(strNumber);
    for (int i = 0; i < length; i++)
    {
        number[i] = strNumber[i] - '0';
    }
    printNumber(number, length);
    generateNums(number, length);

    return 0;
}

void swap(int *a, int i, int j)
{
    int s = a[i];
    a[i] = a[j];
    a[j] = s;
}

void generateNums(int *a, int n)
{
    int j = n - 2;
    while (j != -1 && a[j] >= a[j + 1])
    {
        j--;
    }
    if (j == -1)
    {
        return; // больше перестановок нет
    }
    int k = n - 1;
    while (a[j] >= a[k])
    {
        k--;
    }
    swap(a, j, k);
    int l = j + 1, r = n - 1; // сортируем оставшуюся часть последовательности
    while (l < r)
    {
        swap(a, l++, r--);
    }
    printNumber(a, n);
    return generateNums(a, n);
}

void printNumber(int *a, int n)
{
    static int num = 1;
    printf("%d: ", num++);

    for (int i = 0; i < n; i++)
    {
        printf("%d", a[i]);
    }
    printf("\n");
}
