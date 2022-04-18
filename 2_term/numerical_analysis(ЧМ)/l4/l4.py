import sys

import numpy as np

matrix = [
    [0.83, 1.41, 0.58, 2.71],
    [1.23, 0.83, 1.17, 5.26],
    [1.43, 1.58, 0.83, 1.03],
]


def gauss_method(mtrx):
    n = len(mtrx)
    x = np.zeros(n)

    # Applying Gauss Jordan Elimination
    for i in range(n):
        if mtrx[i][i] == 0.0:
            sys.exit("Divide by zero detected!")

        for j in range(n):
            if i != j:
                ratio = mtrx[j][i] / mtrx[i][i]

                for k in range(n + 1):
                    mtrx[j][k] = mtrx[j][k] - ratio * mtrx[i][k]

    # Obtaining Solution
    for i in range(n):
        x[i] = mtrx[i][n] / mtrx[i][i]

    # Displaying solution
    print("\nRequired solution is: ")
    for i in range(n):
        print("X%d = %0.2f" % (i, x[i]), end="\t")


if __name__ == "__main__":
    gauss_method(matrix)
