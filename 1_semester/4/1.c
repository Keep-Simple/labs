#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef struct Vowels
{
    char value;
    int usageCount;
} vowelsUsage;

int vowelsUsageComparator(const void *a, const void *b)
{
    vowelsUsage *ia = (vowelsUsage *)a;
    vowelsUsage *ib = (vowelsUsage *)b;
    return ib->usageCount - ia->usageCount;
}

int main()
{
    printf("Task 4\n");

    printf("Enter sentence to perform analysis. Sentence must end with \".\" : ");
    char sentence[1000];
    scanf("%[^/.]s", sentence);

    vowelsUsage vowels[] = {
        {value : 'a', usageCount : 0},
        {value : 'e', usageCount : 0},
        {value : 'i', usageCount : 0},
        {value : 'o', usageCount : 0},
        {value : 'u', usageCount : 0},
    };

    const int vowelsLenght = sizeof(vowels) / sizeof(vowels[0]);

    for (int i = 0; i < strlen(sentence); i++)
    {
        for (int j = 0; j < vowelsLenght; j++)
        {
            if (vowels[j].value == tolower(sentence[i]))
            {
                vowels[j].usageCount++;
            }
        }
    }

    qsort(vowels, vowelsLenght, sizeof(vowels[0]), vowelsUsageComparator);

    int totalUsageCount = 0;

    for (int j = 0; j < vowelsLenght; j++)
    {
        totalUsageCount += vowels[j].usageCount;
    }

    for (int j = 0; j < vowelsLenght; j++)
    {
        float usageRate = (vowels[j].usageCount * 100) / totalUsageCount;
        printf("Vowel: %c, has %.2f%% usage rate\n", vowels[j].value, usageRate);
    }

    return 0;
}
