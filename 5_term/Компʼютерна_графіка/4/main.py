from enum import StrEnum, auto
from tkinter import Button, OptionMenu, StringVar, Tk, filedialog

import cv2
import numpy as np


class FilterOptions(StrEnum):
    BlackAndWhite = auto()
    Negative = auto()
    Blur = auto()


def apply_filter(image, filter_type):
    match filter_type:
        case FilterOptions.BlackAndWhite:
            return cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        case FilterOptions.Negative:
            return cv2.bitwise_not(image)
        case FilterOptions.Blur:
            return cv2.filter2D(
                src=image, ddepth=-1, kernel=np.ones((5, 5), np.float32) / 25
            )
        case _:
            return image


def open_image(filter_type):
    file_path = filedialog.askopenfilename()
    image = cv2.imread(file_path)
    cv2.imshow("Original", image)
    filtered_image = apply_filter(image, filter_type)
    cv2.imshow("Modified", filtered_image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


def render():
    root = Tk()
    root.title("Photo filters")
    filter_var = StringVar(root)
    filter_var.set(FilterOptions.Blur)
    filter_options = OptionMenu(
        root,
        filter_var,
        FilterOptions.BlackAndWhite,
        FilterOptions.Negative,
        FilterOptions.Blur,
    )
    filter_options.pack()

    open_button = Button(
        root, text="Add Photo", command=lambda: open_image(filter_var.get())
    )
    open_button.pack()
    root.mainloop()


render()
