from sorting.array_generators import gen_1, gen_2, gen_3, gen_4, gen_5, gen_6
from sorting.bubble_sort import sort_buble
# from sorting.count_sort import count_sort
# from sorting.heap_sort import heap_sort
from sorting.insertion_sort import insertion_sort
from sorting.merge_sort import merge_sort
from sorting.quick_sort import quick_sort
from sorting.selection_sort import selection_sort
from sorting.shell_sort import shell_sort

asc_comparator = lambda x, y: x > y
desc_comparator = lambda x, y: x < y

options = (
    ("Bubble Sort", sort_buble, gen_1, asc_comparator),
    ("Selection Sort", selection_sort, gen_2, desc_comparator),
    ("Shell Sort", shell_sort, gen_3, desc_comparator),
    ("Quick Sort", quick_sort, gen_4, desc_comparator),
    ("Merge Sort", merge_sort, gen_5, asc_comparator),
    ("Insertion Sort", insertion_sort, gen_6, asc_comparator),
    # ("Count Sort", count_sort, gen_2),
    # ("Heap Sort", heap_sort, gen_6),
)

FRAME_INTERVAL = 50
