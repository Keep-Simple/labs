import textwrap

from constants import MAX_VIOLATIONS_COUNT
from leader_server.global_vars import posts
from leader_server.models.post import Post
from leader_server.utils.auth_middleware import auth_middleware
from leader_server.utils.check_for_bad_word import validate_post_content


@auth_middleware
def create_post(user, payload):
    content = payload["content"]
    if not content:
        return {
            "type": "error",
            "message": "Post can't be empty",
        }

    ok, violations_count, violations_map = validate_post_content(content)

    print(violations_map)

    if not ok:
        return {
            "type": "error",
            "message": textwrap.dedent(
                f"""Post content violated forum rules.
                   Allowed violations count is {MAX_VIOLATIONS_COUNT},
                   found {violations_count}
                """
            ),
            "payload": violations_map,
        }

    if violations_count == -1:
        return {
            "type": "error",
            "message": textwrap.dedent(
                """Post content validation failed.
                Please try again :(
                """
            ),
        }

    new_post = Post(content, user.id)
    posts.append(new_post)
    return {
        "type": "ok",
        "message": "Your post was added",
        "payload": new_post.id,
    }
