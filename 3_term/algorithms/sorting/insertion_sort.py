from sorting.utils import swap


def insertion_sort(arr):
    if len(arr) == 1:
        return
    for i in range(1, len(arr)):
        j = i
        while j > 0 and arr[j - 1] > arr[j]:
            swap(arr, j, j - 1)
            j -= 1
            yield arr
