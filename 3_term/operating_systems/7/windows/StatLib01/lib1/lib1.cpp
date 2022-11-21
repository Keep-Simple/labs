#include "pch.h"
#include "framework.h"
#include "lib1.h"

int libSumUp(int* arr, int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) sum += arr[i];
    return sum;
}
