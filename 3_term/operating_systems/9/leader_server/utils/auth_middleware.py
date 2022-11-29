from leader_server.global_vars import users


def auth_middleware(func):
    def wrapped(data):
        token = data["auth"]["token"]
        for user in users:
            if token == user.token:
                return func(user, data["payload"])
        return {"type": "error", "message": "Incorrect credintials"}

    return wrapped
