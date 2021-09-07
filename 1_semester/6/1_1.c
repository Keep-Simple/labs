#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES

typedef struct Matrix
{
    int **value;
    int x;
    int y;
} matrix;

void initMatrix(matrix *matrix)
{
    matrix->value = (int **)malloc(matrix->y * sizeof(int *));

    for (int i = 0; i < matrix->y; i++)
    {
        matrix->value[i] = (int *)malloc(matrix->x * sizeof(int));
    }

    for (int i = 0; i < matrix->y; i++)
    {
        for (int j = 0; j < matrix->x; j++)
        {
            matrix->value[i][j] = 0;
        }
    }
}

void populateMatrix(matrix *matrix, int *values)
{
    for (int i = 0; i < matrix->y; i++)
    {
        for (int j = 0; j < matrix->x; j++)
        {
            matrix->value[i][j] = values[i * matrix->x + j];
        }
    }
}

void initAndPopulateMatrix(matrix *matrix, int *values)
{
    initMatrix(matrix);
    populateMatrix(matrix, values);
}

void freeMatrix(matrix *matrix)
{
    for (int i = 0; i < matrix->x; i++)
    {
        free(matrix->value[i]);
    }
    free(matrix->value);
}

void addMatrix(matrix *a, matrix *b, matrix *result)
{
    if (a->x != b->x || a->y != b->y)
    {
        printf("Error: matrix sizes aren't equal!");
        return;
    }

    result->x = a->x;
    result->y = a->y;
    initMatrix(result);

    for (int i = 0; i < a->y; i++)
    {
        for (int j = 0; j < a->x; j++)
        {
            result->value[i][j] = a->value[i][j] + b->value[i][j];
        }
    }
}

void printMatrix(matrix *matrix, char *name)
{
    printf("\"%s\" matrix:\n", name);
    for (int i = 0; i < matrix->y; i++)
    {
        for (int j = 0; j < matrix->x; j++)
        {
            printf("\t%d", matrix->value[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    printf("Task 5, Section 1\n");
    matrix a, b, result;

    a.x = 3;
    a.y = 3;
    b.x = 3;
    b.y = 3;

    int matrix1[][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    int matrix2[][3] = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}};

    initAndPopulateMatrix(&a, matrix1);
    printMatrix(&a, "Initial");

    initAndPopulateMatrix(&b, matrix2);
    printMatrix(&b, "Transposed");

    addMatrix(&a, &b, &result);
    printMatrix(&result, "Sum");

    freeMatrix(&result);

    return 0;
}