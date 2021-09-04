#include <stdio.h>

#define ARRAY_SIZE 10

void swapArrayElements(int arr[], int oldIdx, int newIdx)
{
    int temp = arr[oldIdx];
    arr[oldIdx] = arr[newIdx];
    *(arr + newIdx) = temp;
}

void reverse(int arr[], int start, int end)
{
    for (int i = start; i <= (start + end) / 2; i++)
    {
        swapArrayElements(arr, i, start + end - i);
    }
}

void cyclicShift(int arr[], int size, int shift)
{
    reverse(arr, 0, size - 1);
    reverse(arr, shift, size - 1);
    reverse(arr, 0, shift - 1);
}

void printArray(int arr[], int size)
{
    printf("array[%d]{", size);

    for (int i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
        if (i != size - 1)
        {
            printf(", ");
        }
    }

    printf("}\n");
}

int main()
{
    printf("Task 5 from 1st section\n");
    int array[ARRAY_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    printf("Array before cyclic 2 shift\n");
    printArray(array, ARRAY_SIZE);

    cyclicShift(array, ARRAY_SIZE, 2);

    printf("Array after\n");
    printArray(array, ARRAY_SIZE);
    return 0;
}