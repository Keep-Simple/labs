from leader_server.global_vars import users
from leader_server.models.user import User
from leader_server.utils.password import gen_salted_password, is_same_password
from leader_server.utils.random_string import gen_random_string


def login(data):
    payload = data["payload"]
    for user in users:
        if user.name == payload["name"]:
            if is_same_password(payload["password"], user.password):
                print("Login Success")
                return {
                    "type": "ok",
                    "payload": user.token,
                    "message": f"User {user.name} is logged in",
                }
            else:
                print("Login Failed")
                return {
                    "type": "error",
                    "message": f"User {user.name} has wrong password",
                }

    print("Login creating new user...")
    new_user = User(
        name=payload["name"],
        password=gen_salted_password(payload["password"]),
        token=gen_random_string(),
    )

    users.append(new_user)

    return {
        "type": "ok",
        "payload": new_user.token,
        "message": f"User {new_user.name} is logged in",
    }
