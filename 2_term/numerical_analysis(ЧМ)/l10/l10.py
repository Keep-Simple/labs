import json
import math
import string

import numpy as np


def f(x):
    return np.sqrt(x) * np.log(1 + np.cbrt(x**2))


a = 0
b = 3
eps = 0.0001


def left_rectangle_method(f, a, b, n):
    h = (b - a) / n

    def f_xi(i):
        return f(a + i * h)

    return h * np.sum([f_xi(i) for i in range(n - 1)])


def right_rectangle_method(f, a, b, n):
    h = (b - a) / n

    def f_xi(i):
        return f(a + i * h)

    return h * np.sum([f_xi(i) for i in range(1, n)])


def central_rectangle_method(f, a, b, n):
    h = (b - a) / n

    def f_xi(i):
        return f(a + i * h)

    return h * np.sum([f_xi(i + 0.5) for i in range(n - 1)])


def trapezium_method(f, a, b, n):
    h = (b - a) / n

    def f_xi(i):
        return f(a + i * h)

    trapezium = h * np.sum([(f_xi(i) + f_xi(i + 1)) / 2 for i in range(n - 1)])

    return trapezium


def simpson_method(f, a, b, n):
    h = (b - a) / n

    def f_xi(i):
        return f(a + i * h)

    simpson = (h / 3) * (
        f_xi(0)
        + f_xi(n)
        + 4 * np.sum([f_xi(i - 1) for i in range(1, n) if i % 2])
        + 2 * np.sum([f_xi(i) for i in range(1, n - 1) if i % 2])
    )

    return simpson


def snake_case_to_pascal_case(str):
    return string.capwords(str.replace("_", " ")).replace(" ", "")


if __name__ == "__main__":
    for method in [
        right_rectangle_method,
        left_rectangle_method,
        central_rectangle_method,
        trapezium_method,
        simpson_method,
    ]:
        print(f"With eps={eps}|>")
        print(snake_case_to_pascal_case(method.__name__))
        n = math.ceil((b - a) / (eps ** (0.5)))
        prev_res = None

        while True:
            print(">")
            print(f"n={n}")
            res = method(f, a, b, n)
            print(json.dumps(res, indent=4))
            if not prev_res or math.fabs(res - prev_res) > eps:
                n *= 2
            else:
                break
            prev_res = res
        print("-------------------------------")
