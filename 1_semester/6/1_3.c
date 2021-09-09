#include <stdio.h>
#include <math.h>

// Задати макрос обчислення n - ого члена геометричної прогресії за введеними користувачем першим членом і знаменником
#define GET_N_GEOM_PROGRESSION_ELEMENT(firstEl, base, n) firstEl *pow(base, n - 1)

int main(void)
{
    printf("Task 5, Section 3\n");

    double base, firstElement;

    printf("Enter base and first element: ");
    scanf("%lf %lf", &base, &firstElement);

    printf("Result: %.3lf\n", GET_N_GEOM_PROGRESSION_ELEMENT(firstElement, base, 3));

    return 0;
}
