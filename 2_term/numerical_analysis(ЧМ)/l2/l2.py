import math

from l1.l1 import equality as f
from l1.l1 import validate_range
from scipy import misc, special


def IterationsMethod(calc_x, x=1, eps=1e-2):
    step = 1
    condition = True
    while condition:
        x1 = calc_x(x)
        step += 1
        condition = math.fabs(x - x1) > eps
        x = x1

    return {"result": x, "iterations": step}


def f1(x):
    return special.cbrt(6 * x**2 + 7)


def f2(x):
    return x - f(x) / misc.derivative(f, x)


def run():
    try:
        eps = float(input("Tolerable Error [0.01]: ") or 1e-2)
        start = float(input("Interval start [2+√6]: ") or 2 + math.sqrt(6))
        end = float(input("Interval end [10]:") or 10)
        validate_range(f, start, end, eps)

        # pick initial x value
        x = end
        if f(start) * misc.derivative(f, start, n=2) > 0:
            x = start

        newtons_res = IterationsMethod(f2, x, eps)
        simple_iterations_res = IterationsMethod(f1, x, eps)

        print(
            f"""
            Newtons method:
                x = {newtons_res["result"]:.6f}
                iterations = {newtons_res["iterations"]}

            Simple Iterations method:
                x = {simple_iterations_res["result"]:.6f}
                iterations = {simple_iterations_res["iterations"]}
        """
        )

    except Exception as e:
        print(
            f"""Something went wrong, try again!
            Error: {e}"""
        )


if __name__ == "__main__":
    run()
