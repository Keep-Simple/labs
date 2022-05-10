import math
from typing import Tuple

import numpy as np
from l4.l4 import back_sub, forward_sub, print_matrix, run_method

A = np.array(
    [
        [2, -1, -2],
        [3, 1, -5],
        [2, -4, 3],
        [0, -1, -5],
        [-1, 3, 2],
    ],
    dtype=np.double,
)

B = np.array([7, -1, -13, 14, 7], dtype=np.double)


def least_squares(A: np.ndarray, B: np.ndarray):
    """
    Transform AX = B -> NX = C
    N = A transposed * A
    C = A transposed * B

    N = L * L transposed
    L * Y = C -> forward sub
    L transposed * X = Y -> back sub
    """
    AT = A.transpose()
    N = np.dot(AT, A)
    C = np.dot(AT, B)
    N_det = np.linalg.det(N)

    print_matrix(AT, "A transposed (AT)")
    print_matrix(N, "N = AT * A")
    print_matrix([C], "C = AT * B")
    print(f"\nDeterminant of N = {N_det}")

    if N_det <= 0:
        return []

    L, LT = square_decomposition(N)
    print_matrix(L, "L")
    print_matrix(LT, "L transposed")

    y = forward_sub(L, C)
    x = back_sub(LT, y)
    print_matrix([x], "x")
    print_matrix([y], "y")

    print("\nVerifying results: NX - C = ", np.dot(N, x) - C)
    return x


def square_decomposition(N: np.ndarray) -> Tuple[np.ndarray, np.ndarray]:
    n = N.shape[0]
    L = np.zeros(N.shape)

    L[0, 0] = math.sqrt(N[0, 0])
    for i in range(0, n):
        for j in range(0, n):
            if j == 0:
                L[i, 0] = N[i, 0] / L[0, 0]
                continue
            if i == j:
                L[i, i] = math.sqrt(N[i, i] - sum([L[i, p] ** 2 for p in range(0, i)]))
                continue
            if i > j:
                L[i, j] = (N[i, j] - sum([L[i, p] * L[j, p] for p in range(0, j)])) / L[
                    j, j
                ]

    return L, L.transpose()


if __name__ == "__main__":
    run_method(method_name="Smallest Squares", method=least_squares, A=A, B=B)
