from leader_server.models.post import Post
from leader_server.utils.auth_middleware import auth_middleware


@auth_middleware
def view_posts(db, me, *_):
    payload = []
    posts = db.query(Post).join(Post.user)

    for post in posts:
        entry = {}
        entry["content"] = post.content

        if me.id == post.user_id:
            entry["user_name"] = f"Me ({me.name})"
        else:
            entry["user_name"] = post.user.name
        payload.append(entry)

    return {
        "type": "ok",
        "message": "Posts were successfully retrieved",
        "payload": payload,
    }
