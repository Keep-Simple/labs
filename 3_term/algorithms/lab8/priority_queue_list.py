class ListNode:
    def __init__(self, val, prio):
        self.val = val
        self.prio = prio
        self.next = None

    def __str__(self):
        return f"Node(value={self.val}, priority={self.prio})"


class PriorityQueue:
    def __init__(self):
        self.root = None
        self.length = 0

    def pop_left(self):
        if not self.root:
            return None
        old_root = self.root
        self.root = self.root.next
        self.length -= 1
        return old_root

    def push(self, val, priority):
        new_node = ListNode(val, priority)
        self.length += 1

        # edge case: root is None
        if not self.root:
            self.root = new_node
            return

        # edge case: swap with root
        if self.root.prio < priority:
            self.root, new_node.next = new_node, self.root
            return

        it = self.root
        while it and it.next and it.prio >= priority:
            it = it.next
        it.next, new_node.next = new_node, it.next

    def merge(self, pq2):
        self.length += len(pq2)

        pq1 = self.root
        pq2 = pq2.root
        dummy_new_root = ListNode(0, 0)
        it = dummy_new_root

        while pq1 and pq2:
            if pq1.prio > pq2.prio:
                it.next = pq1
                pq1 = pq1.next
            else:
                it.next = pq2
                pq2 = pq2.next
            it = it.next

        while pq1:
            it.next = pq1
            it = it.next
            pq1 = pq1.next
        while pq2:
            it.next = pq2
            it = it.next
            pq2 = pq2.next

        self.root = dummy_new_root.next

        return self.root

    def __iter__(self):
        self.it = self.root
        return self

    def __next__(self):
        curr = self.it
        if not curr:
            raise StopIteration()

        self.it = self.it.next
        return curr

    def __len__(self):
        return self.length
