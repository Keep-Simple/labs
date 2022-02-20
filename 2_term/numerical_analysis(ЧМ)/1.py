import math


def bisection(f, a, b, eps):
    validate_range(f, a, b, eps)

    step = 1
    condition = True
    while condition:
        mid = (a + b) / 2

        if f(a) * f(mid) < 0:
            b = mid
        else:
            a = mid

        step += 1
        condition = math.fabs(a - b) > eps

    return {"result": mid, "iterations": step}


def secant(f, a, b, eps):
    validate_range(f, a, b, eps)

    step = 1
    condition = True
    while condition:
        b, a = a - (f(a) * (b - a)) / (f(b) - f(a)), b
        step += 1
        condition = math.fabs(a - b) > eps

    return {"result": b, "iterations": step}


def equality(x):
    return x**3 - 6 * x**2 - 7


def validate_range(f, a, b, eps):
    if f(a) * f(b) > 0:
        raise ValueError(f"Given values [{a}, {b}] do not bracket the root")

    if eps == 0:
        raise ValueError(f"Eps must be > 0, but was {eps}")


def run(start, end):
    try:
        eps = float(input("Tolerable Error [0.0001]: ") or 0.0001)

        bisection_res = bisection(equality, start, end, eps)
        hord_res = secant(equality, start, end, eps)

        print(
            f"""
            Bisection method:
                x = {bisection_res["result"]}
                iterations = {bisection_res["iterations"]}

            Secant method:
                x = {hord_res["result"]}
                iterations = {hord_res["iterations"]}
        """
        )
    except Exception as e:
        print(
            f"""Something went wrong, try again!
            Error: {e}"""
        )


run(start=2 + math.sqrt(6), end=10)
