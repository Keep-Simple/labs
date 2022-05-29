import numpy as np

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
    yp = 0  # interpolated value

    for i in range(n):
        p = 1
        for j in range(n):
            if i == j:
                continue
            p *= (x0 - x_points[j]) / (x_points[i] - x_points[j])
        print(f"step: {i+1}, y={yp}")
        yp += p * y_points[i]

    print(f"y0={yp}")
    return yp


# Steps:
# [-] Calculating f(x_prev, x_curr) and f(x_prev, x_curr, x_next)
# whereas f(x_prev, x_curr, x_next) equals to ...
# (f(x_curr, x_next) - f(x_prev, x_curr)) / x_next - x_prev
# [-] Building the table of values
# rows: [x_i | f_i | f(x_i, x_ii) | f(x_i, x_ii, x_iii)]
# [-] Using formula calculating the polynomial
def newton_at_x(points, x0):
    print(f"\nNewton method for x0={x0}:")
    x_points, y_points = points
    m = len(x_points)
    a_coff = np.copy(y_points)

    for k in range(1, m):
        a_coff[k:m] = (a_coff[k:m] - a_coff[k - 1]) / (x_points[k:m] - x_points[k - 1])

    n = len(x_points) - 1  # Degree of polynomial
    yp = a_coff[n]

    for k in range(1, n + 1):
        yp = a_coff[n - k] + (x0 - x_points[n - k]) * yp
        print(f"step: {k}, y={yp}")

    print(f"y0={yp}")
    return yp


if __name__ == "__main__":
    lagrange_at_x(points, x0)
    newton_at_x(points, x0)
    print
