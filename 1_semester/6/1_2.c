#include <stdio.h>
#include <stdarg.h>

void parseNumber(int);

void calcArgsDigits(int firstNumber, ...)
{
    int currentNum;
    va_list args;
    va_start(args, &firstNumber);

    parseNumber(firstNumber);
    // read args while current element not -1
    while ((currentNum = va_arg(args, int)) != -1)
    {
        parseNumber(currentNum);
    }
    va_end(args);
}

typedef struct DigitFrequency
{
    int digit;
    int count;
} digitFrequency;

void parseNumber(int number)
{
    int numberCopy = number;
    digitFrequency map[10];

    for (int i = 0; i < 10; i++)
    {
        map[i].digit = i;
        map[i].count = 0;
    }

    while (numberCopy)
    {
        int digit = numberCopy % 10;
        map[digit].count++;
        numberCopy /= 10;
    }

    printf("Parsing number \"%d\":\n", number);
    for (int i = 0; i < 10; i++)
    {
        printf("\t\"%d\" used %d times\n", map[i].digit, map[i].count);
    }
}

int main()
{
    printf("Task 5, Section 2\n");

    calcArgsDigits(1000, 22394, 3393939, 4999, 51111, 6120390756, -1);

    return 0;
}