import re
from multiprocessing import Process, Queue
from typing import List

from constants import MAX_VIOLATIONS_COUNT


def check_for_bad_word(queue, content, bad_word):
    if len(content) < len(bad_word):
        queue.put((bad_word, 0))
        return

    count = 0

    for _ in re.finditer(
        "(?=%s)(?!.{1,%d}%s)" % (bad_word, len(bad_word) - 1, bad_word),
        content,
    ):
        count += 1

    queue.put((bad_word, count))


def validate_post_content(
    content: str, bad_words: List[str]
) -> tuple[bool, int, dict[str, int]]:
    try:
        q = Queue()
        processes = []
        results = {}
        total_count = 0
        ok = True

        for bad_word in bad_words:
            p = Process(
                target=check_for_bad_word,
                args=(
                    q,
                    content,
                    bad_word,
                ),
            )
            processes.append(p)
            p.start()

        for _ in processes:
            bad_word, count = q.get()
            results[bad_word] = count
            total_count += count

        for p in processes:
            p.join()

        if total_count > MAX_VIOLATIONS_COUNT:
            ok = False

        return ok, total_count, results
    except Exception as e:
        print("Error during content validation", e)
        return False, -1, {}
