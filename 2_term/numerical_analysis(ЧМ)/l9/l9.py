import matplotlib.pyplot as plt
import numpy as np
from l4.l4 import lu, print_matrix

points = (
    np.array([0.72, 0.79, 0.9, 1.01, 1.1, 1.15]),
    np.array([2.8, 2.94, 3.2, 3.38, 3.53, 3.75]),
)


def polyfit(x, y, degree):
    m = degree + 1
    n = len(x)
    A = np.zeros((m, m))
    B = np.zeros(m)

    for k in range(m):
        for i in range(n):
            B[k] += y[i] * (x[i] ** k)
            for j in range(m):
                A[k][j] += x[i] ** (j + k)

    print_matrix(A, "A")
    print_matrix([B], "B")
    coeffs = lu(A, B, mute=True)
    return np.poly1d(coeffs[::-1])


def least_squares_approximation(points, degree):
    p = polyfit(points[0], points[1], degree)
    polyline = np.linspace(np.min(points[0]), np.max(points[0]) * 1.5)
    plt.plot(*points, "*")
    plt.plot(polyline, p(polyline), "--")
    plt.xlabel("x")
    plt.ylabel("y")
    print(p)
    plt.show()


if __name__ == "__main__":
    print("Initial points:")
    print_matrix([points[0]], "X")
    print_matrix([points[1]], "Y")

    least_squares_approximation(points, 1)
    least_squares_approximation(points, 2)
    least_squares_approximation(points, 3)
