import random

from lab9.rb_tree import RedBlackTree


def gen_random_real_array(n):
    return random.sample(range(-1000, 1000), n)


# Варіант 15: N, M – матриці цілих чисел розміром 3*3
# (використовувати середнє значення елементів для впорядкування);
# матриці з середнім значенням елементів менше за 100


class Matrix:
    def __init__(self, fixed_av=None):
        if fixed_av:
            self.data = [[fixed_av]]
        else:
            self.data = [gen_random_real_array(3) for _ in range(3)]

    def _avarage(self):
        sum = 0
        for row in self.data:
            for cell in row:
                sum += cell
        return sum / (len(self.data * len(self.data[0])))

    def __lt__(self, other):
        return self._avarage() < other._avarage()

    def __eq__(self, other):
        return abs(self._avarage() - other._avarage()) < 0.1

    def __repr__(self):
        return "%.1f" % self._avarage()

    def __str__(self):
        return "%.1f" % self._avarage()

    def print_str(self):
        return "\n".join("\t".join("%0.3f" % x for x in y) for y in self.data)


if __name__ == "__main__":
    N = int(input("Welcome!\nPlease enter number N: ") or 10)

    bst = RedBlackTree()
    for _ in range(N):
        mtrx = Matrix()
        bst.insert(mtrx)
        print(f"Inserting: {mtrx}")
        res = bst.search_less_than(Matrix(100))
        print(f"Values less than 100: {res}")
        print()

    while True:
        M = float(input("Please enter value to search: ") or 10.0)
        v = bst.search_tree(Matrix(M))

        if v == bst.TNULL:
            print("Not found")
            continue

        print(f"Found: {v.item} ({bst.get_node_color(v)})")

        if not v.parent or v.parent == bst.TNULL:
            print("No parent node")
        else:
            print(f"Parent: {v.parent.item} ({bst.get_node_color(v.parent)})")

        if not v.left or v.left == bst.TNULL:
            print("No left node")
        else:
            print(f"Left node: {v.left.item} ({bst.get_node_color(v.left)})")

        if not v.right or v.right == bst.TNULL:
            print("No right node")
        else:
            print(f"Right node: {v.right.item} ({bst.get_node_color(v.right)})")

        print()
