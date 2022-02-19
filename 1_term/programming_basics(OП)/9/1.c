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
        arrayLength = strtol(arrayEntry, 0, 10) + 1;

        int *arr = (int *)malloc(sizeof(int) * arrayLength);
        int retry = 0;

        while (arrayEntry)
        {
            if (i == arrayLength)
            {
                fprintf(stderr, "\nError: number of elements must be: %d. This array won't be persisted.\n\n", arrayLength - 1);
                i = 0;
                free(arr);
                retry = 1;
                break;
            }
            arr[i++] = strtol(arrayEntry, 0, 10);
            arrayEntry = strtok(NULL, spaceDelim);
        }

        if (retry)
            continue;

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

        free(arrays[i]);
    }

    return 0;
}
