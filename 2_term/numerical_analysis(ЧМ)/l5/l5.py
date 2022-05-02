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

# [ 1.89409123  1.70513871  2.13676697 -2.79149157]


if __name__ == "__main__":
    run_method(method_name="Iterations", method=None, A=A, B=B)
    run_method(method_name="Jacobi", method=None, A=A, B=B)
