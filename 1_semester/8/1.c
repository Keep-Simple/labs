#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS_COUNT 100
#define MAX_LINE_LENGTH 512
struct Students {
  struct Student {
    char name[30], surname[50], birthDate[14];
    struct Grades {
      int entries[20];
      int length;
      double avarage;
    };

    struct Grades grades;
  };

  struct Student entries[100];
  int length;
  double avarageGrade;
};

struct Date {
  int day;
  int month;
  int year;
};

void getStudentsFromFile(struct Students *students) {
  FILE *file = fopen("students.txt", "r");

  char buffer[MAX_LINE_LENGTH];
  char comaDelim[] = ",";
  char spaceDelim[] = " ";

  int studentsCount = 0, gradesCount = 0, gradesSum = 0;
  double totalGradesSum = 0;

  while (fgets(buffer, MAX_LINE_LENGTH, file)) {
    char *entry = strtok(buffer, comaDelim);
    strcpy(students->entries[studentsCount].surname, entry);
    entry = strtok(NULL, comaDelim);
    strcpy(students->entries[studentsCount].name, entry);
    entry = strtok(NULL, comaDelim);
    strcpy(students->entries[studentsCount].birthDate, entry);
    entry = strtok(NULL, comaDelim);
    entry[strcspn(entry, "\n")] = 0;

    // reuse entry variable for parsing space separated grades
    entry = strtok(entry, spaceDelim);
    while (entry != NULL) {
      gradesSum +=
          (students->entries[studentsCount].grades.entries[gradesCount++] =
               atoi(entry));
      entry = strtok(NULL, spaceDelim);
    }
    students->entries[studentsCount].grades.length = gradesCount;
    totalGradesSum += (students->entries[studentsCount].grades.avarage =
                           (double)gradesSum / gradesCount);

    gradesCount = 0;
    gradesSum = 0;
    studentsCount++;
  }
  students->length = studentsCount;
  students->avarageGrade = totalGradesSum / studentsCount;
  fclose(file);
}

void getParsedDate(char *str, struct Date *date) {
  const char dotDelim[] = ".";
  char *datePart = strtok(str, dotDelim);
  date->day = atoi(datePart);
  datePart = strtok(NULL, dotDelim);
  date->month = atoi(datePart);
  datePart = strtok(NULL, dotDelim);
  date->year = atoi(datePart);
}

int studentsAgeComparator(const void *a, const void *b) {
  struct Student *ia = (struct Student *)a;
  struct Student *ib = (struct Student *)b;
  struct Date dateA, dateB;

  getParsedDate(ia->birthDate, &dateA);
  getParsedDate(ib->birthDate, &dateB);

  if (dateA.year != dateB.year)
    return dateA.year - dateB.year;

  if (dateA.month != dateB.month)
    return dateA.month - dateB.month;

  if (dateA.day != dateB.day)
    return dateA.day - dateB.day;

  return 0;
}

void printStudents(struct Students *students) {
  for (int i = 0; i < students->length; i++) {
    printf("Student %d:\n\tSurname: %s\n\tName: %s\n\tAvarage Grade: %.3lf\n\n",
           i + 1, students->entries[i].surname, students->entries[i].name,
           students->entries[i].grades.avarage);
  }
}

int main(void) {
  printf("Task 3:\n\n");

  struct Students students;
  getStudentsFromFile(&students);

  // create students array, where each student has less than avarage grade
  struct Students filteredStudents;
  filteredStudents.length = 0;

  for (int i = 0; i < students.length; i++) {
    if (students.entries[i].grades.avarage < students.avarageGrade) {
      // shallow copy
      filteredStudents.entries[filteredStudents.length++] = students.entries[i];
    }
  }

  // sort by age
  qsort(filteredStudents.entries, filteredStudents.length,
        sizeof(filteredStudents.entries[0]), studentsAgeComparator);

  printStudents(&filteredStudents);

  return 0;
}
