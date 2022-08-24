import random
import string


def random_word(n):
    letters = string.ascii_lowercase
    return "".join(random.choice(letters) for _ in range(n))


def gen_random_real_array(n, include_negative=True):
    return [random.uniform(-n if include_negative else 0, n) for _ in range(n)]
