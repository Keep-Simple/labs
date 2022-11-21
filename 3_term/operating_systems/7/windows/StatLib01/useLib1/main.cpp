#include <Windows.h>

#include <iostream>

#include "lib1.h"
//#define RUNTIME_LOAD
#ifndef RUNTIME_LOAD
#include "dll1.h"
#include "main.h"
#else
typedef int(__cdecl* DLLSUMUP)(int*, int);
#endif

int main() {
  int len;
  std::cout << "Type array size: ";
  std::cin >> len;
  int* arr = new int[len];
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  for (int i = 0; i < len; i++) arr[i] = rand() % 10;

  int sum = libSumUp(arr, len);
  std::cout << "Sum from static lib: " << sum << std::endl;

#ifndef RUNTIME_LOAD
  int dllSum = dllSumUp(arr, len);
  std::cout << "Sum from dynamic lib (using load-time linking): " << dllSum
            << std::endl;
#else
    HINSTANCE hinstLib;
    DLLSUMUP sumFn;

    hinstLib = LoadLibrary(TEXT("dll1.dll"));

    if (!hinstLib) {
        std::cout << "Failed to load ddl" << std::endl;
        return -1;
    }

    sumFn = (DLLSUMUP)GetProcAddress(hinstLib, "dllSumUp");

    if (!sumFn) {
        std::cout << "Failed to link dll on runtime" << std::endl;
    } else {
        int sum = sumFn(arr, len);
        std::cout << "Sum from dynamic lib (using run-time linking): " << sum
            << std::endl;
    }

    FreeLibrary(hinstLib);
#endif
}

