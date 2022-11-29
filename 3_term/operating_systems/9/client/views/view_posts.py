import pytermgui as ptg

import client.views.create_post
from client.socket_client import socket_client


def client_view_posts(ui):
    posts = view_posts(ui)
    post_widgets = [ptg.Collapsible(p["user_name"], p["content"]) for p in posts]

    window = ptg.Window(
        ptg.Button(
            "Create Post",
            lambda *_: client.views.create_post.client_create_post_form(
                ui, client.views.create_post.create_post
            ),
        ),
        "",
        "View posts",
        *post_widgets
    )

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
