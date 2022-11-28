from leader_server.global_vars import posts
from leader_server.utils.auth_middleware import auth_middleware


@auth_middleware
def view_posts(*_):
    return {
        "type": "ok",
        "message": "Posts were successfully retrieved",
        "payload": list(map(lambda p: p.__dict__, posts)),
    }
