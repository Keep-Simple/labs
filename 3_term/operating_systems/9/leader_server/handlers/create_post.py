from leader_server.global_vars import posts
from leader_server.models.post import Post
from leader_server.utils.auth_middleware import auth_middleware


@auth_middleware
def create_post(user, payload):
    new_post = Post(payload["content"], user.id)
    posts.append(new_post)
    return {
        "type": "ok",
        "message": "Your post was added",
        "payload": new_post.id,
    }
