import random

import matplotlib.animation as anim
import matplotlib.pyplot as plt
from sorting.bubble_sort import sort_buble
from sorting.count_sort import count_sort
from sorting.heap_sort import heap_sort
from sorting.insertion_sort import insertion_sort
from sorting.merge_sort import merge_sort
from sorting.quick_sort import quick_sort
from sorting.selection_sort import selection_sort
from sorting.shell_sort import shell_sort


def animate_sort(array, algo, title):
    n = len(array)
    fig, ax = plt.subplots()
    ax.set_title(title)
    bar_rec = ax.bar(range(n), array, align="edge")
    ax.set_xlim(0, n)
    ax.set_ylim(0, int(n * 1.1))
    text = ax.text(0.02, 0.95, "", transform=ax.transAxes)
    # due to black magic
    iterations = [0]

    def update_plot(array, rec, iterations):
        for rec, val in zip(rec, array):
            rec.set_height(val)
        iterations[0] += 1
        text.set_text(f"Operations count :{iterations[0]}")

    _ = anim.FuncAnimation(
        fig,
        func=update_plot,
        fargs=(bar_rec, iterations),
        frames=algo,
        interval=1,
        repeat=False,
    )
    plt.show()


def gen_random_array():
    n = int(input("Welcome to the sorting visualizer!\nPlease enter the array size: "))
    array = [i + 1 for i in range(n)]
    random.shuffle(array)
    return array


def pick_sort_from_cli(array):
    n = len(array)
    options = (
        ("Bubble Sort", sort_buble(array)),
        ("Insertion Sort", insertion_sort(array)),
        ("Quick Sort", quick_sort(array, 0, n - 1)),
        ("Selection Sort", selection_sort(array)),
        ("Merge Sort", merge_sort(array, 0, n - 1)),
        ("Heap Sort", heap_sort(array)),
        ("Shell Sort", shell_sort(array)),
        ("Count Sort", count_sort(array)),
        ("Bubble Sort", sort_buble(array)),
    )
    options_str = [f"\t{idx}.{option[0]}" for idx, option in enumerate(options)]
    query_str = "\n".join(["Pick algorithm number:", *options_str, "\t"])
    picked = int(input(query_str))

    return options[picked] if 0 <= picked < len(options) else options[0]


array = gen_random_array()
title, algo = pick_sort_from_cli(array)
animate_sort(array, algo, title)
