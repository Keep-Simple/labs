def swap(A, i, j):
    A[i], A[j] = A[j], A[i]


def quick_sort(arr, comparator):
    return _quick_sort(arr, 0, len(arr) - 1, comparator)


def _quick_sort(arr, a, b, comparator):
    if a >= b:
        return
    piv = arr[b]
    piv_idx = a
    for i in range(a, b):
        if comparator(arr[i], piv):
            swap(arr, i, piv_idx)
            piv_idx += 1
        yield arr
    swap(arr, b, piv_idx)
    yield arr

    yield from _quick_sort(arr, a, piv_idx - 1, comparator)
    yield from _quick_sort(arr, piv_idx + 1, b, comparator)
