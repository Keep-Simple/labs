from sorting.utils import swap


def heapify(arr, n, i):
    largest = i
    l = i * 2 + 1
    r = i * 2 + 2
    while l < n and arr[l] > arr[largest]:
        largest = l
    while r < n and arr[r] > arr[largest]:
        largest = r
    if largest != i:
        swap(arr, i, largest)
        yield arr
        yield from heapify(arr, n, largest)


def heap_sort(arr):
    n = len(arr)
    for i in range(n, -1, -1):
        yield from heapify(arr, n, i)
    for i in range(n - 1, 0, -1):
        swap(arr, 0, i)
        yield arr
        yield from heapify(arr, i, 0)
