import pytermgui as ptg

from client.socket_client import socket_client
from client.views.view_posts import client_view_posts

PROMT_TO_KEY = {"Name: ": "name", "Password: ": "password"}


def client_login_form(ui, callback):
    def submit(window: ptg.Window) -> None:
        output = {}
        for widget in window:
            if isinstance(widget, ptg.InputField):
                key = PROMT_TO_KEY[widget.prompt]
                output[key] = widget.value
                continue
        callback(ui, output)
        ui.remove(window)

    inputs = [ptg.InputField(prompt=prompt) for prompt in PROMT_TO_KEY.keys()]
    window = ptg.Window(
        "[secondary]Login",
        "",
        *inputs,
        "",
        ["Submit", lambda *_: submit(window)],
    ).center()
    ui.add(window)


def login(ui, creds):
    res = socket_client.send_request(
        ui=ui,
        method="login",
        payload=creds,
    )

    if res is None:
        # retry login
        client_login_form(ui, login)
        return

    socket_client.set_token(res)

    client_view_posts(ui)
