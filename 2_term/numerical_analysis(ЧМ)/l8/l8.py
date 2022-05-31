import numpy as np
from l4.l4 import print_matrix

points = (
    np.array(
        [
            0.115,
            0.12,
            0.125,
            0.13,
            0.135,
            0.14,
            0.145,
            0.15,
            0.165,
            0.17,
        ]
    ),
    np.array([4.48, 4.95, 5.47, 5.99, 6.05, 6.68, 6.909, 7.38, 8.166, 9.025]),
)
x0 = 0.142


def lagrange_at_x(points, x0):
    print(f"\nLagrange method for x0={x0}:")
    x_points, y_points = points

    n = len(x_points)
    y0 = 0  # interpolated value

    for i in range(n):
        p = 1
        for j in range(n):
            if i == j:
                continue
            p *= (x0 - x_points[j]) / (x_points[i] - x_points[j])
        y0 += p * y_points[i]

    print(f"Result: y0={y0}")
    return y0


def newton_at_x(points, x0):
    print(f"\nNewton method for x0={x0}:")
    x_points, y_points = points
    a_coff = np.copy(y_points)

    for k in range(1, len(x_points)):
        a_coff[k:] = (a_coff[k:] - a_coff[k - 1]) / (x_points[k:] - x_points[k - 1])

    print_matrix([a_coff], "Newton differences table (first row)")

    n = len(x_points) - 1
    y0 = a_coff[n]

    for k in range(1, n + 1):
        y0 = a_coff[n - k] + (x0 - x_points[n - k]) * y0

    print(f"\nResult: y0={y0}")
    return y0


if __name__ == "__main__":
    print("Initial points:")
    print_matrix([points[0]], "X")
    print_matrix([points[1]], "Y")

    lagrange_at_x(points, x0)
    newton_at_x(points, x0)
