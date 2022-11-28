import pytermgui as ptg

import client.views.view_posts
from client.socket_client import socket_client

PROMPT_TO_KEY = {"Content: ": "content"}


def client_create_post_form(ui, callback):
    def post(window: ptg.Window) -> None:
        output = {}
        for widget in window:
            if isinstance(widget, ptg.InputField):
                key = PROMPT_TO_KEY[widget.prompt]
                output[key] = widget.value
                continue
        callback(ui, output)
        ui.remove(window)

    inputs = [ptg.InputField(prompt=prompt) for prompt in PROMPT_TO_KEY.keys()]
    window = ptg.Window(
        "[secondary]Create post",
        "",
        *inputs,
        "",
        ["Post", lambda *_: post(window)],
    ).center()
    ui.add(window)


def create_post(ui, form_data):
    res = socket_client.send_request(
        ui=ui,
        method="create_post",
        payload=form_data,
    )
    if res is None:
        client_create_post_form(ui, create_post)
        return

    client.views.view_posts.client_view_posts(ui)
