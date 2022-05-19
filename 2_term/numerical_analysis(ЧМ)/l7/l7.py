import math

import numpy as np
from l4.l4 import gauss_elim

# sin(x+0.5) - y = 1
# cos(y-2) + x = 0


def simple_iterations(tolerance=1e-4):
    x_i, y_i = 0, 0
    print(
        f"""\nSimple iterations method:
                Initial guess: {[x_i,y_i]}
                Tolerance: {tolerance}
            """
    )

    f1 = lambda x: math.sin(x + 0.5) - 1
    f2 = lambda y: -math.cos(y - 2)

    x_ii, y_ii = x_i, y_i
    iterations = 0

    while True:
        iterations += 1
        x_ii, y_ii = f2(y_i), f1(x_i)
        precision = abs(x_ii - x_i) + abs(y_ii - y_i)
        x_i, y_i = x_ii, y_ii

        print(f"{iterations}: x={x_i:.5f}, y={y_i:.5f}, precision={precision:.5f}")

        if precision < tolerance:
            break


def newton_iterations(tolerance=1e-4):
    X = np.array([0, 0], dtype=float)
    print(
        f"""\nNewtons method:
                Initial guess: {X}
                Tolerance: {tolerance}
            """
    )

    def f(X):
        x, y = X
        return np.array([math.sin(x + 0.5) - y - 1, math.cos(y - 2) + x])

    def Jf(X):
        x, y = X
        return np.array([[math.cos(x + 0.5), -1], [1, -math.sin(y - 2)]])

    X_delta = X.copy()
    iterations = 0
    while True:
        iterations += 1
        A = Jf(X)
        B = f(X)
        X_delta = gauss_elim(A, B, mute=True)
        X -= X_delta
        norm = np.linalg.norm(B)

        print(f"{iterations}: x={X[0]:.5f}, y={X[1]:.5f}, norm={norm:.5f}")

        if norm < tolerance:
            break


if __name__ == "__main__":
    simple_iterations()
    newton_iterations()
    print
