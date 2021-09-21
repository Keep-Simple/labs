#include <stdio.h>
#include <string.h>

const int MAX_LINE_LENGTH = 256;
const char spaceDelim[] = " ";

int main(void)
{
    printf("Task 7:\n");

    char line[MAX_LINE_LENGTH], yesOrNo[10];
    char *arrayEntry;
    int *arrays[5];
    int arraysCount = 0, arrayLength, i = 0;

    while (1)
    {
        if (arraysCount == 5)
        {
            fprintf(stderr, "\nYou reached 5 array limit!\n");
            break;
        }
        printf("Enter array elements (space separated), first number is elements count: ");
        fgets(line, MAX_LINE_LENGTH, stdin);
        if (!line)
            break;

        arrayEntry = strtok(line, spaceDelim);
        arrayLength = atoi(arrayEntry) + 1;

        int *arr = (int *)malloc(sizeof(int) * arrayLength);

        while (arrayEntry)
        {
            if (i == arrayLength)
            {
                fprintf(stderr, "\nError: number of elements must match first element: %d. This array won't be persisted.\n\n", arrayLength);
                i = 0;
                free(arr);
                continue;
            }
            arr[i++] = atoi(arrayEntry);
            arrayEntry = strtok(NULL, spaceDelim);
        }

        arrays[arraysCount++] = arr;
        i = 0;

        printf("Add another array? [Y/n]: ");
        gets(yesOrNo);
        if (!strcmp(yesOrNo, "n"))
            break;
    }

    printf("\nArray generation completed. Printing results...\n");
    for (int i = 0; i < arraysCount; i++)
    {
        printf("Array %d: { ", i + 1);
        for (int j = 0; j <= arrays[i][0]; j++)
        {
            if (j == arrays[i][0])
                printf("%d", arrays[i][j]);
            else
                printf("%d, ", arrays[i][j]);
        }
        printf(" }\n");
    }

    return 0;
}
