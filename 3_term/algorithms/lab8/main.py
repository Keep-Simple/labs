import pprint
import random
import string

from lab8.priority_queue_list import PriorityQueue


def gen_input_data(n):
    def get_random_char():
        return random.choice(string.ascii_letters)

    def get_random_prio():
        return random.choice(range(1, 101))

    return [(get_random_char(), get_random_prio()) for _ in range(n)]


def show_statistics(pq):
    min_el = max_el = pq.root
    pre_min_el = None
    second_from_end = third_el = None
    n = len(pq)

    for idx, el in enumerate(pq):
        if idx == 2:
            third_el = el

        if idx == n - 2:
            second_from_end = el

        if min_el.val > el.val:
            pre_min_el = min_el
            min_el = el

        if max_el.val < el.val:
            max_el = el

    print(
        f"""\
          Elements count: {len(pq)}
          Min element: {min_el}
          Max element: {max_el}
          3rd element from the start: {third_el}
          2nd element from the end: {second_from_end}
          Pre-min element: {pre_min_el}
          Post-max element: {max_el.next if max_el else None}
          """
    )


def populate_pq(n):
    pq = PriorityQueue()
    data = gen_input_data(n)
    for char, prio in data:
        pq.push(char, prio)
    print("Created Priority Queue (based on LinkedList)")
    pp = pprint.PrettyPrinter(width=60, compact=True)
    print(f"From data:\n {pp.pformat(data)}\n")
    return pq


def main():
    pq = populate_pq(100)
    pq2 = populate_pq(200)

    print("Statistics:")
    show_statistics(pq)

    pq.merge(pq2)
    print("Statistics After merge:")
    show_statistics(pq)


main()
