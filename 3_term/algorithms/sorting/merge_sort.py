def merge_sort(arr, comparator):
    return _merge_sort(arr, 0, len(arr) - 1, comparator)


def _merge_sort(arr, lb, ub, comparator):
    if ub <= lb:
        return
    elif lb < ub:
        mid = (lb + ub) // 2
        yield from _merge_sort(arr, lb, mid, comparator)
        yield from _merge_sort(arr, mid + 1, ub, comparator)
        yield from _merge(arr, lb, mid, ub, comparator)
        yield arr


def _merge(arr, lb, mid, ub, comparator):
    new = []
    i = lb
    j = mid + 1
    while i <= mid and j <= ub:
        if not comparator(arr[i], arr[j]):
            new.append(arr[i])
            i += 1
        else:
            new.append(arr[j])
            j += 1
    if i > mid:
        while j <= ub:
            new.append(arr[j])
            j += 1
    else:
        while i <= mid:
            new.append(arr[i])
            i += 1
    for i, val in enumerate(new):
        arr[lb + i] = val
        yield arr
