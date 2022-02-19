import math


def equality(x):
    return x**3 - 6 * x**2 - 7


def bisection(f, a, b, eps):
    if f(a) * f(b) > 0 or eps == 0:
        raise ValueError("Given values do not bracket the root or eps == 0")

    step = 1
    condition = True
    while condition:
        mid = (a + b) / 2

        if f(a) * f(mid) < 0:
            b = mid
        else:
            a = mid

        step += 1
        condition = math.fabs(f(mid)) > eps

    return {"result": mid, "iterations": step}


def secant(f, a, b, eps):
    x = a
    x_prev = a + 2 * eps
    i = 0

    while abs(x - x_prev) >= eps and i < b:
        x, x_prev = x - f(x) / (f(x) - f(x_prev)) * (x - x_prev), x
        i += 1

    return {"result": x, "iterations": i}


start = 2 + math.sqrt(6)
end = 10

try:
    eps = float(input("Tolerable Error: "))

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
