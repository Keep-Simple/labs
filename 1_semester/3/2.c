#include <stdio.h>
#include <math.h>

int genRandomInt()
{
    return rand() % 10000;
}

int **generateMatrix(int x, int y)
{
    int **matrix = (int **)malloc(x * sizeof(int *));

    for (int i = 0; i < x; i++)
    {
        matrix[i] = (int *)malloc(y * sizeof(int));
    }

    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            *(*(matrix + i) + j) = genRandomInt();
        }
    }

    return matrix;
}

void freeMatrix(int **matrix, int x, int y)
{
    for (int i = 0; i < x; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void printRowWithBiggestDiagNum(int **matrix, int x, int y)
{
    if (x != y)
    {
        printf("Error: matrix must be square\n");
        return;
    }

    int maxElementRowIdx = 0;
    for (int i = 0; i < x; i++)
    {
        if (matrix[i][i] > matrix[maxElementRowIdx][maxElementRowIdx])
        {
            maxElementRowIdx = i;
        }
    }

    printf("\nPrinting row with biggest diagonal number: \n");
    for (int i = 0; i < x; i++)
    {
        printf("%d ", matrix[maxElementRowIdx][i]);
    }
    printf("\n");
}

void printMatrix(int **matrix, int x, int y)
{
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    printf("Task 5 from 2nd section\n\n");

    const MATRIX_SIZE = 5;
    int **matrix = generateMatrix(MATRIX_SIZE, MATRIX_SIZE);

    printMatrix(matrix, MATRIX_SIZE, MATRIX_SIZE);

    printRowWithBiggestDiagNum(matrix, MATRIX_SIZE, MATRIX_SIZE);

    freeMatrix(matrix, MATRIX_SIZE, MATRIX_SIZE);
    return 0;
}