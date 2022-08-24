def swap(A, i, j):
    A[i], A[j] = A[j], A[i]


def selection_sort(arr, comparator):
    for i in range(len(arr) - 1):
        min = i
        for j in range(i + 1, len(arr)):
            if not comparator(arr[j], arr[min]):
                min = j
            yield arr
        if min != i:
            swap(arr, i, min)
            yield arr
