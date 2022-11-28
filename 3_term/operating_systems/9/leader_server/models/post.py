from leader_server.utils.random_string import gen_random_string


class Post:
    def __init__(self, content, user_id):
        self.id = gen_random_string()
        self.user_id = user_id
        self.content = content
