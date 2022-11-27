"""
15. Дано текст що складається з n стрічок.
Визначити чи є серед даного тексту цифри, якщо є вилучити їх з тексту.
Знайти задане слово в тексті.

Виміряти час пошуку,
а також час (окремо) додаткового опрацювання тексту та/чи взірця,
якщо таке є.
"""

from lab12.boyer_moore import bm_search

TEXT = """Lorem Ipsum is simply dummy text of the printing and typesetting industry.
Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book.
It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged.
It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages,
and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum."""

TEXT_2 = "cabcbbbcabca"
# SEARCH_PATTERN_2 = "cabca"
SEARCH_PATTERN_2 = "cabca"

# txt = "ABAAABCD"
# pat = "ABC"


def get_input_text(_search_pattern=None):
    text = []
    for char in TEXT_2:
        if not char.isnumeric():
            text.append(char)
    text_str = "".join(text)
    print(f"Text: \n{text_str}\n")
    if _search_pattern:
        return text_str, _search_pattern
    search_pattern = input("Please enter search pattern: ")
    return text_str, search_pattern


if __name__ == "__main__":
    # while True:
    text, search_pattern = get_input_text(SEARCH_PATTERN_2)
    bm_search(text, search_pattern)
    print()
