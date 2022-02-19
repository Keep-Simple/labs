#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student
{
    char name[30], surname[50];
    double grade;
    int year;
    struct Student *next;
} student;

student *createStudent()
{
    student *s = malloc(sizeof(student));
    s->next = NULL;

    return s;
}

void printList(student *head)
{
    printf("_____________\n");
    while (head)
    {
        printf("student: %d\n", head->year);
        head = head->next;
    }
    printf("_____________\n");
}

void deleteLast(student **head)
{
    student *temp = *head;

    if (!temp || !temp->next)
    {
        *head = NULL;
        return;
    }

    while (temp->next->next)
        temp = temp->next;

    free(temp->next);
    temp->next = NULL;
}

void deleteFirst(student **head)
{
    student *temp = *head;
    if (!temp)
        return;

    *head = temp->next;
    free(temp);
}

// n from 1
void deleteNth(student **head, int n)
{
    student *temp = *head;
    if (!temp)
        return;

    // delete First
    if (n == 1)
    {
        *head = temp->next;
        free(temp);
        return;
    }

    // find prev node
    for (int i = 0; temp && i < n - 2; i++)
        temp = temp->next;

    // If position is more than number of nodes
    if (!temp || !temp->next)
        return;

    // delete nth
    student *next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

void swap(student **p1, student **p2)
{
    student *temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void swapNodes(student **head, int i, int j)
{
    student **p1 = head, **p2 = head;

    while (*p1 && i-- > 0)
        p1 = &(*p1)->next;
    while (*p2 && j-- > 0)
        p2 = &(*p2)->next;

    if (*p1 && *p2)
    {
        swap(p1, p2);
        swap(&(*p1)->next, &(*p2)->next);
    }
}

int main(void)
{
    student *head = NULL, *temp;

    for (int i = 0; i < 5; i++)
    {
        temp = createStudent();
        temp->next = head;
        temp->year = i;
        head = temp;
    }

    printList(head);
    // swapNodes(&head, 1, 3);
    // swapNodes(&head, 1, 3);
    swapNodes(&head, 0, 4);
    printList(head);

    // deleteLast(&head);

    // printList(head);

    // deleteFirst(&head);
    // deleteFirst(&head);

    // printList(head);

    // deleteNth(&head, 2);

    // printList(head);
    return 0;
}
