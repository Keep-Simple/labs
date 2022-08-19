from sorting.utils import swap


def selection_sort(arr):
    for i in range(len(arr) - 1):
        min = i
        for j in range(i + 1, len(arr)):
            if arr[j] < arr[min]:
                min = j
            yield arr
        if min != i:
            swap(arr, i, min)
            yield arr
