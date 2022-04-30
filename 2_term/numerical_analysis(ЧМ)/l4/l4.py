from math import fabs

import numpy as np

A = np.array(
    [
        [0.83, 1.41, 0.58],
        [1.23, 0.83, 1.17],
        [1.43, 1.58, 0.83],
    ]
)

B = np.array([2.71, 5.26, 1.03])


def gaussElim(a, b):
    n = len(b)

    # Elimination phase
    for k in range(n - 1):
        # find the best raw
        for i in range(k + 1, n):
            if fabs(a[i, k]) > fabs(a[k, k]):
                a[[k, i]] = a[[i, k]]
                b[[k, i]] = b[[i, k]]
                break

        for i in range(k + 1, n):
            if a[i, k] != 0.0:
                cof = a[i, k] / a[k, k]
                # calculate the new row
                a[i] = a[i] - cof * a[k]
                # update vector b
                b[i] = b[i] - cof * b[k]
        print(f"Iteration {k}:")
        _print_a_and_b(a, b)

    # backward substitution
    x = np.zeros(n)
    for k in range(n - 1, -1, -1):
        x[k] = (b[k] - np.dot(a[k, k + 1 : n], x[k + 1 : n])) / a[k, k]

    return x


def _print_a_and_b(a, b):
    print("A:")
    print_matrix(a)
    print("B:")
    print(b)
    print()


def print_matrix(mtrx):
    s = [[str(e) for e in row] for row in mtrx]
    lens = [max(map(len, col)) for col in zip(*s)]
    fmt = "\t".join("{{:{}}}".format(x) for x in lens)
    table = [fmt.format(*row) for row in s]
    print("\n".join(table))


if __name__ == "__main__":
    print("Initial values:")
    _print_a_and_b(A, B)

    A_COPY = A.copy()  # save original matrix A
    B_COPY = B.copy()  # save original vector b
    X = gaussElim(A, B)

    print("\nResults, X:")
    print(X)

    print("\nChecking results: AX - B = ", np.dot(A_COPY, X) - B_COPY)
    print()
