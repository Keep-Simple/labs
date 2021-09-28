#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES

typedef struct Matrix
{
    double **values;
    int x;
    int y;
} matrix;

void initMatrix(matrix *matrix, int fillFromStd)
{
    matrix->values = (double **)malloc(matrix->y * sizeof(double *));

    for (int i = 0; i < matrix->y; i++)
    {
        matrix->values[i] = (double *)calloc(matrix->x, sizeof(double));
        if (fillFromStd)
        {
            printf("Enter %d elements for %d row:\n", matrix->x, i);
            for (int j = 0; j < matrix->x; j++)
            {
                printf("\tidx %d: ", j);
                scanf("%lf", &matrix->values[i][j]);
            }
            printf("\n");
        }
    }
}

void freeMatrix(matrix *matrix)
{
    for (int i = 0; i < matrix->x; i++)
    {
        free(matrix->values[i]);
    }
    free(matrix->values);
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
    initMatrix(result, 0);

    for (int i = 0; i < a->y; i++)
    {
        for (int j = 0; j < a->x; j++)
        {
            result->values[i][j] = a->values[i][j] + b->values[i][j];
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
            printf("\t%.1lf", matrix->values[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void transposeSquareMatrix(matrix *initial, matrix *out)
{
    if (initial->x != initial->y)
        return;

    out->x = initial->x;
    out->y = initial->y;
    initMatrix(out, 0);

    for (int i = 0; i < initial->y; i++)
        for (int j = 0; j < initial->x; j++)
            out->values[j][i] = initial->values[i][j];
}

int main()
{
    printf("Task 5, Section 1\n");
    printf("Enter matrix heigth and width: ");

    matrix a, b, result;
    int size = 0;
    scanf("%d", &size);
    a.x = a.y = size;

    initMatrix(&a, 1);
    printMatrix(&a, "Initial");

    transposeSquareMatrix(&a, &b);
    printMatrix(&b, "Transposed");

    addMatrix(&a, &b, &result);
    printMatrix(&result, "Sum");

    freeMatrix(&result);
    freeMatrix(&a);
    freeMatrix(&b);

    return 0;
}