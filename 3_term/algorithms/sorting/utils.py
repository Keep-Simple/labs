import random
import signal
import string
import time


def random_word(n):
    letters = string.ascii_lowercase
    return "".join(random.choice(letters) for _ in range(n))


def gen_random_real_array(n, include_negative=True):
    return [random.uniform(-n if include_negative else 0, n) for _ in range(n)]


class TimeoutError(Exception):
    def __init__(self, value="Timed Out"):
        self.value = value

    def __str__(self):
        return repr(self.value)


def timeout(seconds_before_timeout):
    def decorate(f):
        def handler(signum, frame):
            raise TimeoutError()

        def new_f(*args, **kwargs):
            old = signal.signal(signal.SIGALRM, handler)
            old_time_left = signal.alarm(seconds_before_timeout)
            if (
                0 < old_time_left < seconds_before_timeout
            ):  # never lengthen existing timer
                signal.alarm(old_time_left)
            start_time = time.time()
            try:
                result = f(*args, **kwargs)
            finally:
                if old_time_left > 0:  # deduct f's run time from the saved timer
                    old_time_left -= time.time() - start_time
                signal.signal(signal.SIGALRM, old)
                signal.alarm(old_time_left)
            return result

        # new_f.func_name = f.func_name
        return new_f

    return decorate
