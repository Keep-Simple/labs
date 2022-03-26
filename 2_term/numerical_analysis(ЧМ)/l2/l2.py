from scipy import misc, special
import l1.l1 as lab1
import math


def IterationsMethod(calc_x, x=1, tolerance=1e-2):
    step = 1
    condition = True
    while condition:
        x1 = calc_x(x)
        step += 1
        condition = math.fabs(x - x1) > tolerance
        x = x1

    return {"result": x, "iterations": step}


f = lab1.equality


def f1(x):
    return special.cbrt(6 * x**2 + 7)


def f2(x):
    return x - f(x) / misc.derivative(f, x)


def validate_range(f, a, b, eps):
    if f(a) * f(b) > 0:
        raise ValueError(f"Given values [{a}, {b}] do not bracket the root")

    if eps == 0:
        raise ValueError(f"Eps must be > 0, but was {eps}")


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
