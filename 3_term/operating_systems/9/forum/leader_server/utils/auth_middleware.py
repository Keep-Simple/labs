from leader_server.models.user import User


def auth_middleware(func):
    def wrapped(db, data):
        token = data["auth"]["token"]
        user = db.query(User).filter(User.token == token).first()

        if user:
            return func(db, user, data["payload"])

        return {"type": "error", "message": "Incorrect credintials"}

    return wrapped
