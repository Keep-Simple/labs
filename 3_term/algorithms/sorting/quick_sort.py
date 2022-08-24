def swap(A, i, j):
    A[i], A[j] = A[j], A[i]


def quick_sort(arr, comparator):
    return _quick_sort(arr, 0, len(arr) - 1, comparator)


def _quick_sort(arr, p, q, comparator):
    if p >= q:
        return
    piv = arr[q]
    pivindx = p
    for i in range(p, q):
        if comparator(arr[i], piv):
            swap(arr, i, pivindx)
            pivindx += 1
        yield arr
    swap(arr, q, pivindx)
    yield arr

    yield from _quick_sort(arr, p, pivindx - 1, comparator)
    yield from _quick_sort(arr, pivindx + 1, q, comparator)
