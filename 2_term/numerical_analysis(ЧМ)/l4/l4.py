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


def gauss_elim(A, B):
    n = len(B)

    # Elimination phase
    for k in range(n - 1):
        # find the best raw
        for i in range(k + 1, n):
            if fabs(A[i, k]) > fabs(A[k, k]):
                A[[k, i]] = A[[i, k]]
                B[[k, i]] = B[[i, k]]
                break

        for i in range(k + 1, n):
            if A[i, k] != 0.0:
                cof = A[i, k] / A[k, k]
                # calculate the new row
                A[i] = A[i] - cof * A[k]
                # update vector b
                B[i] = B[i] - cof * B[k]
        print(f"\nIteration {k}:")
        _print_a_and_b(A, B)

    # backward substitution
    x = np.zeros(n)
    for k in range(n - 1, -1, -1):
        x[k] = (B[k] - np.dot(A[k, k + 1 : n], x[k + 1 : n])) / A[k, k]

    return x


def lu_solve(L, U, P, B):
    def forward_sub(L, b):
        """solution to Lx = b
        L must be a lower-triangular matrix
        b must be a vector of the same leading dimension as L
        """
        n = len(L)
        x = np.zeros(n)
        for i in range(n):
            sum = 0
            for j in range(i):
                sum += L[i, j] * x[j]
            x[i] = (b[i] - sum) / L[i, i]
        return x

    def back_sub(U, b):
        """solution to Ux = b
        U must be an upper-triangular matrix
        b must be a vector of the same leading dimension as U
        """
        n = len(U)
        x = np.zeros(n)
        for i in range(n - 1, -1, -1):
            sum = 0
            for j in range(n - 1, i, -1):
                sum += U[i, j] * x[j]
            x[i] = (b[i] - sum) / U[i, i]
        return x

    y = forward_sub(L, np.dot(P, B))
    x = back_sub(U, y)
    return x


def lu_decompose(A):
    """
    Decomposes a matrix A by PA=LU
    """

    def pivotize(m):
        """
        Creates the pivoting matrix for m.
        """
        n = len(m)
        ID = [[float(i == j) for i in range(n)] for j in range(n)]
        for j in range(n):
            row = max(range(j, n), key=lambda i: abs(m[i][j]))
            if j != row:
                ID[j], ID[row] = ID[row], ID[j]
        return ID

    n = len(A)
    L = np.zeros((n, n))
    U = np.zeros((n, n))
    P = np.asarray(pivotize(A))
    PA = np.dot(P, A)
    for j in range(n):
        L[j][j] = 1.0
        for i in range(j + 1):
            s1 = sum(U[k][j] * L[i][k] for k in range(i))
            U[i][j] = PA[i][j] - s1
        for i in range(j, n):
            s2 = sum(U[k][j] * L[i][k] for k in range(j))
            L[i][j] = (PA[i][j] - s2) / U[j][j]

    return L, U, P


def _print_a_and_b(a, b):
    print("A:")
    print_matrix(a)
    print("B:")
    print(b)


def print_matrix(mtrx):
    s = [[str(e) for e in row] for row in mtrx]
    lens = [max(map(len, col)) for col in zip(*s)]
    fmt = "\t".join("{{:{}}}".format(x) for x in lens)
    table = [fmt.format(*row) for row in s]
    print("\n".join(table))


if __name__ == "__main__":
    print("Initial values:")
    _print_a_and_b(A, B)

    print("\n\nGause method:")
    x = gauss_elim(A.copy(), B.copy())
    print("\nResulting vector x:")
    print(x)
    print("\nVerifying results: AX - B = ", np.dot(A, x) - B)

    print("\n\nLU method:")
    L, U, P = lu_decompose(A.copy())

    print("\nL:")
    print_matrix(L)
    print("\nU:")
    print_matrix(U)
    print("\nP:")
    print_matrix(P)
    print("\nIs LU = PA:", np.array_equal(np.dot(L, U), np.dot(P, A)))

    x = lu_solve(L, U, P, B.copy())
    print("\nResulting vector x:")
    print(x)

    print("\nVerifying results: AX - B = ", np.dot(A, x) - B)
