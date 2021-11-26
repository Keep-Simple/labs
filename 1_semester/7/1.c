#include <math.h>
#include <stdio.h>
#include <time.h>

void swap(int array[], long pos1, long pos2)
{
  long tmp = array[pos1];
  array[pos1] = array[pos2];
  array[pos2] = tmp;
}

void quickSort(int array[], long start, long end)
{
  long head = start, tail = end - 1, tmp;
  long diff = end - start;
  long pe_index;
  // якщо залишилося менше двох елементів – кінець рекурсії
  if (diff < 1)
    return;
  if (diff == 1)
    if (array[start] > array[end])
    {
      swap(array, start, end);
      return;
    }
  // пошук індексу розділяючого елементу pe_index
  long m = (start + end) / 2;
  if (array[start] <= array[m])
  {
    if (array[m] <= array[end])
      pe_index = m;
    else if (array[end] <= array[start])
      pe_index = start;
    else
      pe_index = end;
  }
  else
  {
    if (array[start] >= array[end])
      pe_index = start;
    else if (array[end] >= array[m])
      pe_index = m;
    else
      pe_index = end;
  }
  long pe = array[pe_index]; // сам розділяючий елемент
  swap(array, pe_index, end);
  while (1)
  {
    while (array[head] < pe)
      ++head;
    while (array[tail] > pe && tail > start)
      --tail;
    if (head >= tail)
      break;
    swap(array, head++, tail--);
  }
  swap(array, head, end);
  long mid = head;
  quickSort(array, start, mid - 1); // рекурсивний виклик для 1-ої підмножини
  quickSort(array, mid + 1, end);   // рекурсивний виклик для 2-ої підмножини
}

void bubbleSort(int array[], int length)
{
  for (int i = 0; i < length - 1; i++)
  {
    for (int j = 0; j < length - i - 1; j++)
    {
      if (array[j] > array[j + 1])
      {
        swap(array, j + 1, j);
      }
    }
  }
}

void printArray(int arr[], int size)
{
  printf("\nArray[%d] {", size);

  for (int i = 0; i < size; i++)
  {
    printf("%d", arr[i]);
    if (i >= 100)
    {
      printf(" ...%d more elements}\n", size - i);
      return;
    }
    if (i != size - 1)
    {
      printf(", ");
    }
  }

  printf("}\n");
}

int isArraySortedAsc(int arr[], int length)
{
  for (int i = 0; i < length - 1; i++)
  {
    if (arr[i] > arr[i + 1])
    {
      return 0;
    }
  }
  return 1;
}

int areArraysEqual(int arr1[], int arr2[], int length)
{
  for (int i = 0; i < length; i++)
  {
    if (arr1[i] != arr2[i])
    {
      return 0;
    }
  }
  return 1;
}

void printExecutionTime(clock_t start, clock_t end)
{
  printf("Time taken: %f sec.\n", (float)(end - start) / CLOCKS_PER_SEC);
}

#define ARRAY_SIZE 200000
int main(void)
{
  printf("Task 5, Section 1:\n");

  int arr1[ARRAY_SIZE], arr2[ARRAY_SIZE];
  clock_t start, end;

  srand(time(NULL));
  for (int i = 0; i < ARRAY_SIZE; i++)
  {
    arr1[i] = rand() % ARRAY_SIZE;
    arr2[i] = arr1[i];
  }

  printf("Initial arrays are %s\n\n",
         areArraysEqual(arr1, arr2, ARRAY_SIZE) ? "identical" : "different");

  // bubble sort
  start = clock();
  bubbleSort(arr1, ARRAY_SIZE);
  end = clock();

  printf("Bubble sort %s:\n",
         isArraySortedAsc(arr1, ARRAY_SIZE) ? "worked" : "failed");
  printExecutionTime(start, end);
  printArray(arr1, ARRAY_SIZE);

  // quick sort
  start = clock();
  quickSort(arr2, 0, ARRAY_SIZE - 1);
  end = clock();

  printf("\nQuick sort %s:\n",
         isArraySortedAsc(arr2, ARRAY_SIZE) ? "worked" : "failed");
  printExecutionTime(start, end);
  printArray(arr2, ARRAY_SIZE);

  printf("\nSorted arrays are %s\n",
         areArraysEqual(arr1, arr2, ARRAY_SIZE) ? "identical" : "different");

  return 0;
}
