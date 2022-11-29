from leader_server.models.user import User
from leader_server.utils.password import gen_salted_password, is_same_password


def login(db, data):
    payload = data["payload"]
    user = db.query(User).filter(User.name == payload["name"]).first()

    if user:
        if is_same_password(payload["password"], user.password):
            print("Login success")
            return {
                "type": "ok",
                "payload": user.token,
                "message": f"User {user.name} is logged in",
            }
        else:
            print("Login failed")
            return {
                "type": "error",
                "message": f"User {user.name} has wrong password",
            }

    new_user = User(
        name=payload["name"],
        password=gen_salted_password(payload["password"]),
    )
    db.add(new_user)
    db.commit()

    print("Created new user and logged in")
    return {
        "type": "ok",
        "payload": new_user.token,
        "message": f"User {new_user.name} is logged in",
    }
