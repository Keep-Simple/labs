#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printNumber(int *a, int n);
void swap(int *a, int *b);
void permutation(int *a, int start, int end);
int *numberToArray(int number, int *length);

int main(void)
{
  printf("Task 6, Section 3:\n");

  int number, digitsCount;
  printf("Enter number: ");
  scanf("%d", &number);

  int *digitsArr = numberToArray(number, &digitsCount);
  permutation(digitsArr, 0, digitsCount - 1);

  return 0;
}

int *numberToArray(int number, int *length)
{
  *length = (int)(log10((float)number)) + 1;
  int *arr = (int *)malloc(*length * sizeof(int)), *curr = arr;

  do
  {
    *curr++ = number % 10;
    number /= 10;
  } while (number != 0);

  return arr;
}

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void permutation(int *a, int start, int end)
{
  if (start == end)
  {
    printNumber(a, end + 1);
    return;
  }

  for (int i = start; i <= end; i++)
  {
    // swapping numbers
    swap((a + i), (a + start));
    // fixing one first digit
    // and calling permutation on
    // the rest of the digits
    permutation(a, start + 1, end);
    swap((a + i), (a + start));
  }
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
