def merge_sort(arr, lb, ub):
    if ub <= lb:
        return
    elif lb < ub:
        mid = (lb + ub) // 2
        yield from merge_sort(arr, lb, mid)
        yield from merge_sort(arr, mid + 1, ub)
        yield from merge(arr, lb, mid, ub)
        yield arr


def merge(arr, lb, mid, ub):
    new = []
    i = lb
    j = mid + 1
    while i <= mid and j <= ub:
        if arr[i] < arr[j]:
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
