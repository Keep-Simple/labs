from leader_server.global_vars import posts, users
from leader_server.utils.auth_middleware import auth_middleware


@auth_middleware
def view_posts(me, *_):
    payload = []
    for post in posts:
        entry = {}
        entry["content"] = post.content

        for user in users:
            if user.id == post.user_id:
                if me.id == post.user_id:
                    entry["user_name"] = f"Me ({user.name})"
                else:
                    entry["user_name"] = user.name
                break

        payload.append(entry)

    return {
        "type": "ok",
        "message": "Posts were successfully retrieved",
        "payload": payload,
    }
