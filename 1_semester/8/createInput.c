#include <stdio.h>
#include <string.h>

int main(void)
{
    char name[30], surname[50], birthDate[14], grades[50];

    printf("Enter students info:\n\tName: ");
    scanf("\n%s", name);
    printf("\tSurname: ");
    scanf("\n%s", surname);
    printf("\tBirth date (dd.mm.yyyy): ");
    scanf("\n%s", birthDate);
    printf("\tGrades (space separeted): ");
    // read empty line (?)
    gets(grades);
    fgets(grades, 100, stdin);

    FILE *file = fopen("students.txt", "a");

    fprintf(file, "%s,%s,%s,%s", surname, name, birthDate, grades);

    fclose(file);

    return 0;
}