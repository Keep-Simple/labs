def swap(A, i, j):
    A[i], A[j] = A[j], A[i]


def heapify(arr, n, i, comparator):
    largest = i
    l = i * 2 + 1
    r = i * 2 + 2
    while l < n and comparator(arr[l], arr[largest]):
        largest = l
    while r < n and comparator(arr[r], arr[largest]):
        largest = r
    if largest != i:
        swap(arr, i, largest)
        yield arr
        yield from heapify(arr, n, largest, comparator)


def heap_sort(arr, comparator):
    n = len(arr)
    for i in range(n, -1, -1):
        yield from heapify(arr, n, i, comparator)
    for i in range(n - 1, 0, -1):
        swap(arr, 0, i)
        yield arr
        yield from heapify(arr, i, 0, comparator)
