#include "pch.h"
#include "dll1.h"

int dllSumUp(int* arr, int len) {
	int sum = 0;
	for (int i = 0; i < len; i++) sum += arr[i];
	return sum;
}
