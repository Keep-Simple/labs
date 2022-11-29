import pytermgui as ptg

import client.views.create_post
from client.socket_client import socket_client


def client_view_posts(ui):
    posts = view_posts(ui)

    layout = ptg.Layout()
    body_slot = layout.add_slot("Body", height=0.6, width=1.0)
    layout.add_break()
    layout.add_slot("Alert", height=0.4, width=1.0)

    post_widgets = [ptg.Collapsible(p["user_name"], p["content"]) for p in posts]

    window = ptg.Window(
        "[bold lightblue]Forums Feed",
        "",
        "",
        ptg.Button(
            "Create Post",
            lambda *_: client.views.create_post.client_create_post_form(
                ui, client.views.create_post.create_post
            ),
        ),
        "",
        *post_widgets,
        overflow=ptg.Overflow.SCROLL,
        box="EMPTY"
    ).center()
    body_slot.content = window
    layout.apply()
    ui.add(window)


def view_posts(ui):
    return (
        socket_client.send_request(
            ui=ui,
            method="view_posts",
            payload=None,
        )
        or []
    )
