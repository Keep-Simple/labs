def swap(A, i, j):
    A[i], A[j] = A[j], A[i]


def sort_buble(arr, comparator):
    if len(arr) == 1:
        return
    for i in range(len(arr) - 1):
        for j in range(len(arr) - 1 - i):
            if comparator(arr[j], arr[j + 1]):
                swap(arr, j, j + 1)
            yield arr
