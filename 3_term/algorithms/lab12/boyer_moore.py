from collections import defaultdict


def bad_char_map(pattern):
    """
    The preprocessing function for
    Boyer Moore's bad character heuristic
    """

    bad_chars = defaultdict(lambda: -1)

    # Fill the actual value of last occurrence
    for i in range(len(pattern)):
        bad_chars[pattern[i]] = i

    # return initialized list
    print(f"{bad_chars=}\n")
    return bad_chars


def bm_search(txt, pattern):
    """
    A pattern searching function that uses Bad Character
    Heuristic of Boyer Moore Algorithm
    """
    m = len(pattern)
    n = len(txt)

    bad_chars = bad_char_map(pattern)

    # s is shift of the pattern with respect to text
    def _print_state(s, j):
        t_display = ["-"] * n
        t_display[s + j] = "*"
        print(f"text and search_pattern:\n{txt}\n{''.join(t_display)}")
        shift_display = [" "] * (s)
        print(f"{''.join(shift_display)}{pattern}\n")

    s = 0
    while s <= n - m:
        j = m - 1

        # Keep reducing index j of pattern while
        # characters of pattern and text are matching
        # at this shift s
        print_state_again = True
        while j >= 0 and pattern[j] == txt[s + j]:
            print("char match")
            print_state_again = False
            _print_state(s, j)
            j -= 1

        if print_state_again:
            _print_state(s, j)

        # If the pattern is present at current shift,
        # then index j will become -1 after the above loop
        if j < 0:
            print("full match at shift = {}!".format(s))

            """
            Shift the pattern so that the next character in text
                aligns with the last occurrence of it in pattern.
            The condition s+m < n is necessary for the case when
            pattern occurs at the end of text
            """
            s += m - bad_chars[txt[s + m]] if s + m < n else 1
            print(f"shift={s}")
        else:
            """
            Shift the pattern so that the bad character in text
            aligns with the last occurrence of it in pattern. The
            max function is used to make sure that we get a positive
            shift. We may get a negative shift if the last occurrence
            of bad character in pattern is on the right side of the
            current character.
            """
            s += max(1, j - bad_chars[txt[s + j]])
            print(f"shift={s}")
