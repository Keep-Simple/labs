#include <stdio.h>
#include <math.h>

// Задати макрос обчислення n - ого члена геометричної прогресії за введеними користувачем першим членом і знаменником
#define GET_N_GEOM_PROGRESSION_ELEMENT(firstEl, base, n) firstEl *pow(base, n - 1)

int main(void)
{
    printf("Task 5, Section 3\n");

    double base, firstElement, idx;

    printf("Enter base, first element, idx of desired element (space-separated): ");
    scanf("%lf %lf %lf", &base, &firstElement, &idx);

    printf("Result: %.3lf\n", GET_N_GEOM_PROGRESSION_ELEMENT(firstElement, base, idx));

    return 0;
}
