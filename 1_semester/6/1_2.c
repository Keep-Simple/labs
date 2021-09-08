#include <stdio.h>
#include <stdarg.h>

// void calcArgsDigits(int firstNumber, ...)
// {
//     int currentNum = firstNumber;
//     va_list args;
//     va_start(args, &firstNumber);

//     // read args while current element not -1
//     while ((currentNum = va_arg(args, int)) != -1)
//     {
//         printf("Number: %d", currentNum);
//     }
//     va_end(args);
// }
void calcArgsDigits(int firstNumber, ...)
{
    int *argsCursor = &firstNumber;

    // read args while current element not -1
    while (*argsCursor != -1)
    {
        printf("Number: %d\n", *argsCursor);
        argsCursor++;
    }
}

int main()
{
    printf("Task 5, Section 2\n");

    calcArgsDigits(1, 2, 3, 4, 5, 6, -1);

    return 0;
}