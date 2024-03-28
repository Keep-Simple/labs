import matplotlib.pyplot as plt
import numpy as np


def func_mandelbrot(c, iterations):
    z = 0
    n = 0
    while abs(z) <= 2 and n < iterations:
        z = z**2 + c
        n += 1
    return n


def mandelbrot_set(x_min, x_max, y_min, y_max, width, height, iterations):
    r1 = np.linspace(x_min, x_max, width)
    r2 = np.linspace(y_min, y_max, height)
    return (
        r1,
        r2,
        np.array(
            [[func_mandelbrot(complex(r, i), iterations) for r in r1] for i in r2]
        ),
    )


def render(xmin, xmax, ymin, ymax, width, height, max_iter):
    d = mandelbrot_set(xmin, xmax, ymin, ymax, width, height, max_iter)
    plt.imshow(d[2], extent=(xmin, xmax, ymin, ymax), cmap="twilight_shifted")
    plt.show()


render(-1.5, 1.5, -1.5, 1.5, 900, 900, 1024)
