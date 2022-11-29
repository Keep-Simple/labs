import textwrap

from constants import MAX_VIOLATIONS_COUNT
from leader_server.models.bad_word import BadWord
from leader_server.models.post import Post
from leader_server.utils.auth_middleware import auth_middleware
from leader_server.utils.check_for_bad_word import validate_post_content


@auth_middleware
def create_post(db, user, payload):
    content = payload["content"]
    if not content:
        return {
            "type": "error",
            "message": "Post can't be empty",
        }

    bad_words = list(map(lambda w: w.value, db.query(BadWord).all()))

    ok, violations_count, violations_map = validate_post_content(
        content,
        bad_words,
    )

    print(f"Validation results for '{content} is {violations_map}'")

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

    new_post = Post(content=content, user_id=user.id)
    db.add(new_post)
    db.commit()
    return {
        "type": "ok",
        "message": "Your post was added",
        "payload": new_post.id,
    }
