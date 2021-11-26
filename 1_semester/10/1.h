#define MAX_STUDENTS_COUNT 100
#define MAX_LINE_LENGTH 512
#define BIRTH_DATE_LENGTH 14

typedef struct Student
{
    char name[30], surname[50], birthDate[BIRTH_DATE_LENGTH];
    struct Grades
    {
        int entries[20];
        int length;
        double avarage;
    } grades;
    struct Student *next;
} student;

struct Date
{
    int day;
    int month;
    int year;
};

student *createStudent();
void insertStudentSorted(student **head, student *newStudent, int (*comparator)(student *a, student *b));
void getParsedDate(char *str, struct Date *date);
int studentsAgeComparator(student *a, student *b);
void addStudentsFromFile(student **head);
void printStudentsList(student *head);
void deleteStudent(student **head, student *studentToDelete);
int studentsGradesMatcher(student *current);
void deleteAllStudentsMatching(student **head, int (*matcher)(student *current));