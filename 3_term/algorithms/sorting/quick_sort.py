from sorting.utils import swap


def quick_sort(arr, p, q):
    if p >= q:
        return
    piv = arr[q]
    pivindx = p
    for i in range(p, q):
        if arr[i] < piv:
            swap(arr, i, pivindx)
            pivindx += 1
        yield arr
    swap(arr, q, pivindx)
    yield arr

    yield from quick_sort(arr, p, pivindx - 1)
    yield from quick_sort(arr, pivindx + 1, q)
