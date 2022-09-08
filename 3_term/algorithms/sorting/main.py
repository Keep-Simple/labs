import matplotlib.animation as anim
import matplotlib.pyplot as plt
from sorting.config import FRAME_INTERVAL, options


def animate_sort(array, algo, title):
    n = len(array)
    fig, ax = plt.subplots()
    ax.set_title(title)
    bar_rec = ax.bar(range(n), array, align="edge")
    ax.set_xlim(0, n)
    ax.set_ylim(min(array), max(array) * 1.2)
    text = ax.text(0.02, 0.95, "", transform=ax.transAxes)
    # due to black magic
    iterations = [0]

    def update_plot(array, rec, iterations):
        for rec, val in zip(rec, array):
            rec.set_height(val)
        iterations[0] += 1
        print(f"Iteration {iterations[0]}: {array}\n")
        text.set_text(f"Operations count :{iterations[0]}")

    _ = anim.FuncAnimation(
        fig,
        func=update_plot,
        fargs=(bar_rec, iterations),
        frames=algo,
        interval=FRAME_INTERVAL,
        repeat=False,
    )
    plt.show()


def ask_array_size():
    return int(
        input("Welcome to the sorting visualizer!\nPlease enter the array size: ") or 10
    )


def pick_sort_from_cli(n):
    options_str = [f"\t{idx+1}.{option[0]}" for idx, option in enumerate(options)]
    query_str = "\n".join(["Pick algorithm number:", *options_str, "\t"])
    picked = (int(input(query_str) or 1) - 1) % len(options)
    title, algo, generator, comparator = options[picked]
    array = generator(n)

    return title, algo(array, comparator), array


n = ask_array_size()
title, algo, array = pick_sort_from_cli(n)
animate_sort(array, algo, title)
