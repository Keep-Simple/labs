from matplotlib.cbook import math
from sorting.utils import gen_random_real_array, random_word


def gen_1(n):
    matrix = [gen_random_real_array(n) for _ in range(n)]
    return [sum(row) for row in matrix]


def gen_2(n):
    arr = gen_random_real_array(n)
    min_el = min(arr)
    for i in range(len(arr)):
        if arr[i] < 0:
            arr[i] *= min_el
    return arr


def gen_3(n):
    arr = gen_random_real_array(n)
    for i in range(len(arr)):
        if i % 2 == 1:
            arr[i] = math.tan(arr[i]) - arr[i]
        else:
            arr[i] = abs(arr[i])
    return arr


def gen_4(n):
    arr = gen_random_real_array(n)

    min_el_idx = max_el_idx = 0
    for i in range(1, len(arr)):
        if arr[i] > arr[max_el_idx]:
            max_el_idx = i
        if arr[i] < arr[min_el_idx]:
            min_el_idx = i

    for i in sorted([min_el_idx, max_el_idx], reverse=True):
        del arr[i]
    return arr


def gen_5(n):
    prices = gen_random_real_array(n, include_negative=False)
    avg = sum(prices) / n
    names = [random_word(6) for _ in range(n)]

    arr = []
    for i in range(n):
        if prices[i] <= avg:
            arr.append(sum(ord(char) for char in names[i]))

    return arr


def gen_6(n):
    arr = gen_random_real_array(n)

    for i in range(len(arr)):
        if i % 2 == 1:
            arr[i] = math.sqrt(abs(arr[i] - 10))

    return arr
