from leader_server.utils.random_string import gen_random_string


class User:
    def __init__(self, name, password, token):
        self.id = gen_random_string()
        self.name = name
        self.password = password
        self.token = token
