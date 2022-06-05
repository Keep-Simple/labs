import json
import string

import numpy as np


def f(x):
    return np.sqrt(x) * np.log(1 + np.cbrt(x**2))


a = 0
b = 3
N = 50


def left_rectangle_method(f, a, b, n=N):
    h = (b - a) / n

    def f_xi(i):
        return f(a + i * h)

    return h * np.sum([f_xi(i) for i in range(n - 1)])


def right_rectangle_method(f, a, b, n=N):
    h = (b - a) / n

    def f_xi(i):
        return f(a + i * h)

    return h * np.sum([f_xi(i) for i in range(1, n)])


def central_rectangle_method(f, a, b, n=N):
    h = (b - a) / n

    def f_xi(i):
        return f(a + i * h)

    return h * np.sum([f_xi(i + 0.5) for i in range(n - 1)])


def trapezium_method(f, a, b, n=N):
    h = (b - a) / n

    def f_xi(i):
        return f(a + i * h)

    trapezium = h * np.sum([(f_xi(i) + f_xi(i + 1)) / 2 for i in range(n - 1)])

    return trapezium


def simpson_method(f, a, b, n=N):
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
        print("--------------------------")
        print(snake_case_to_pascal_case(method.__name__))
        results = []
        for i in range(3):
            n = N * (3**i)
            print(">")
            print(f"n={n}")
            res = method(f, a, b, n)
            results.append(res)
            print(json.dumps(res, indent=4))

        better_res = results[0] - ((results[0] - results[1]) ** 2) / (
            results[0] - 2 * results[1] + results[2]
        )
        print(f"\nAitken interpolation={better_res}")
