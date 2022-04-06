matrix = [
    [0.83, 1.41, 0.58],
    [1.23, 0.83, 1.17],
    [1.43, 1.58, 0.83],
]

constants = [2.71, 5.26, 1.03]


def det(m, nOrder):
    if nOrder == 1:
        return m[0][0]
    z = 0
    for r in range(nOrder):
        k = m[:]
        del k[r]
        z += m[r][0] * (-1) ** r * det([p[1:] for p in k], nOrder - 1)
    return z


def cramer(mtrx, values):
    nOrder = len(values)
    main_det = det(mtrx, nOrder)

    if main_det == 0:
        return []

    res = []

    for i in range(nOrder):
        mtrx_with_changed_column = [
            r[:i] + [s] + r[i + 1 :] for r, s in zip(mtrx, values)
        ]
        res.append(det(mtrx_with_changed_column, nOrder) / main_det)

    return res


def matrix_multply(A, B):
    rows_A = len(A)
    cols_A = len(A[0])
    rows_B = len(B)
    cols_B = len(B[0])

    if cols_A != rows_B:
        raise ValueError("One of the matrices is not eligible for multiplication")

    res = [[0 for _ in range(cols_B)] for _ in range(rows_A)]

    for i in range(rows_A):
        for j in range(cols_B):
            for k in range(cols_A):
                res[i][j] += A[i][k] * B[k][j]
    return res


def matrix_method(eq_matrix, values):
    width = len(values)
    determinant = det(eq_matrix, width)
    # algebraic complements
    ac_matrix = []

    if determinant == 0:
        return []

    for row in range(width):
        ac_row = []

        for column in range(width):
            intermediate = eq_matrix.copy()

            # delete row and column
            intermediate.pop(row)
            intermediate = [
                list(x)
                for x in zip(
                    *[d for i, d in enumerate(zip(*intermediate)) if i != column]
                )
            ]

            minor = det(intermediate, width - 1)
            ac_row.append(pow(-1, row + column) * minor)

        ac_matrix.append(ac_row)

    ac_transposed_matrix = [list(x) for x in zip(*ac_matrix)]
    ac_inverted_matrix = [[z / determinant for z in y] for y in ac_transposed_matrix]

    dot_product = matrix_multply(ac_inverted_matrix, [[v] for v in values])

    return [v[0] for v in dot_product]


if __name__ == "__main__":
    print(
        f"""
            Cramer method:
                x values = {cramer(matrix, constants)}

            Matrix method:
                x values = {matrix_method(matrix, constants)}
        """
    )
