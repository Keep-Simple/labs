import math

tolerance = 1e-4


def f1(x):
    return math.sin(x + 0.5) - 1


def f2(y):
    return -math.cos(y - 2)


def simple_iterations():
    x_i, y_i = 0, 0
    x_ii, y_ii = x_i, y_i
    iterations = 0

    while True:
        iterations += 1
        x_ii, y_ii = f2(y_i), f1(x_i)
        precission = abs(x_ii - x_i) + abs(y_ii - y_i)
        x_i, y_i = x_ii, y_ii

        print(f"{iterations}: x={x_i}, y={y_i}")

        if precission < tolerance:
            break


def newton_iterations():
    ...


if __name__ == "__main__":
    print("Simple iterations method: \n")
    simple_iterations()
    print("\nNewtons method: \n")
    newton_iterations()
    print
