# 15.  Дано одновимірний масив цілих чисел B[і], де і =1,2,…,n.
# Всі елементи масиву, що менші за його середнє арифметичне значення,
# збільшити в 2 рази. Знайти позиції елементів, котрі повторюються k раз.

import random
from collections import defaultdict


def gen_random_int_array(n):
    return [int(random.uniform(-n, n)) for _ in range(n)]


def gen_input_data():
    n = int(input("Welcome!\nPlease enter array size: ") or 100)
    arr = gen_random_int_array(n)
    sum = 0
    for e in arr:
        sum += e
    avg = sum / n

    num_map = defaultdict(int)
    for i in range(n):
        if arr[i] < avg:
            arr[i] *= 2
        num_map[arr[i]] += 1

    arr.sort()
    print(f"Sorted generated array: {arr}")
    k = int(input("Enter number k: ") or 1)
    elements_to_find = [key for key, v in num_map.items() if v == k]

    return arr, elements_to_find


def binary_search(arr, key):
    left, right = 0, len(arr) - 1
    while left <= right:
        mid = (left + right) // 2
        if arr[mid] > key:
            right = mid - 1
        elif arr[mid] < key:
            left = mid + 1
        else:
            return mid


if __name__ == "__main__":
    arr, elements_to_find = gen_input_data()
    print(f"Elements to find {elements_to_find}")

    for el in elements_to_find:
        idx = binary_search(arr, el)
        print(f"Found element {el} with position {idx}")
