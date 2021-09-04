#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include "../1/1.h"

void logWithTimeStampW(const char *format, ...) __attribute__((format(printf, 1, 2)));

void logWithTimeStamp(const char *format, ...)
{
    char *string;
    va_list args;

    va_start(args, format);
    if (0 > vasprintf(&string, format, args))
        string = NULL;
    va_end(args);

    if (string)
    {
        _logWithTimeStamp(string);
        free(string);
    }
    else
    {
        _logWithTimeStamp("Error while logging a message: Memory allocation failed.\n");
    }
}

void _logWithTimeStamp(char str[])
{
    time_t t = time(NULL);
    struct tm *timestamp = localtime(&t);

    FILE *file = fopen("log.txt", "a");

    fprintf(file, "[%02d.%02d.%04d %02d:%02d:%02d] ",
            timestamp->tm_mday,
            timestamp->tm_mon + 1,
            timestamp->tm_year + 1900,
            timestamp->tm_hour,
            timestamp->tm_min,
            timestamp->tm_sec);

    fprintf(file, str);
    fprintf(file, "\n");

    fclose(file);
}

int main(void)
{
    printf("Task from lab 1, addition 1\n");
    logWithTimeStamp("Program started.");

    char argsFile[60];
    printf("Enter binary file containing args, 60 chars max: ");
    scanf("%s", argsFile);

    FILE *file = fopen(argsFile, "rb");
    int x;
    fread(&x, sizeof(x), 1, file);
    logWithTimeStamp("Parameters file \"%s\" opened. x = %d.", argsFile, x);
    fclose(file);

    char outputFile[62];
    char outputFormat;
    printf("Enter output file name (without extension), 60 chars max: ");
    scanf("%s", outputFile);
    printf("Pick output format (b_inary/t_ext) : ");
    scanf(" %c", &outputFormat);

    double calcResult = firstCalcTask(x);
    logWithTimeStamp("Expression calculated. Result = %lf.", calcResult);

    switch (outputFormat)
    {
    case 'b':
        sprintf(outputFile, "%s.%s", outputFile, "bin");
        file = fopen(outputFile, "wb");
        fwrite(&calcResult, sizeof(double), 1, file);
        break;
    case 't':
        sprintf(outputFile, "%s.%s", outputFile, "txt");
        file = fopen(outputFile, "w");
        fprintf(file, "%lf", calcResult);
        break;
    default:
        break;
    }

    logWithTimeStamp("Output file \"%s\" saved.", outputFile);
    fclose(file);
    logWithTimeStamp("Program ended.\n");
    return 0;
}