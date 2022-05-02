import numpy as np
from l4.l4 import run_method

A = np.array(
    [
        [0.55, 0, -0.08, 0.14],
        [0.3, -0.73, -0.12, 0.11],
        [0.17, 0.06, -0.58, 0.12],
        [0.21, -0.16, 0, 0.36],
    ]
)

B = np.array([0.48, -1.24, -1.15, -0.88])


def is_convergent(E):
    norm1 = np.linalg.norm(E, ord=1)
    norm2 = np.linalg.norm(E, ord=np.inf)

    norm3 = 0
    for i in range(E.shape[0]):
        for j in range(E.shape[1]):
            if i != j:
                norm3 += abs((E[i, j] / E[i, i])) ** 2

    norms = [norm1, norm2, norm3]
    print(f"Norms: {norms}")

    return min(norms) < 1


def jacobi(A, B, eps=1e-3, max_iterations=10000):
    x = np.zeros_like(B, dtype=np.double)
    T = A - np.diag(np.diagonal(A))

    for i in range(max_iterations):
        print(f"{i} Iteration:\nx={x}")
        x_old = x.copy()

        x = (B - np.dot(T, x)) / np.diagonal(A)

        if np.linalg.norm(x - x_old, ord=np.inf) / np.linalg.norm(x, ord=np.inf) < eps:
            break

    return x


def seidel(A, B, eps=1e-3, max_iterations=1000):
    x = np.zeros_like(B, dtype=np.double)

    for k in range(max_iterations):
        print(f"{k} Iteration:\nx={x}")
        x_old = x.copy()

        for i in range(A.shape[0]):
            x[i] = (
                B[i]
                - np.dot(A[i, :i], x[:i])
                - np.dot(A[i, (i + 1) :], x_old[(i + 1) :])
            ) / A[i, i]

        if np.linalg.norm(x - x_old, ord=np.inf) / np.linalg.norm(x, ord=np.inf) < eps:
            break

    return x


if __name__ == "__main__":
    if is_convergent(A):
        run_method(method_name="Jacobi", method=jacobi, A=A, B=B)
        run_method(method_name="Seidel", method=seidel, A=A, B=B)
        print
