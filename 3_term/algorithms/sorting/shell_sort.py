def shell_sort(arr, comparator):
    gap = len(arr) // 2
    while gap > 0:
        for start in range(gap):
            yield from gap_insertion_sort(arr, start, gap, comparator)
        gap = gap // 2


def gap_insertion_sort(arr, start, gap, comparator):
    for i in range(start + gap, len(arr), gap):
        current_value = arr[i]

        while i >= gap and comparator(arr[i - gap], current_value):
            arr[i] = arr[i - gap]
            i -= gap
            yield arr

        arr[i] = current_value
        yield arr
