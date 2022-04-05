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


def matrix_method(mtrx, values):
    pass


if __name__ == "__main__":
    print(
        f"""
            Cramer method:
                x values = {cramer(matrix, constants)}

            Matrix method:
                x values = {matrix_method(matrix, constants)}
        """
    )
