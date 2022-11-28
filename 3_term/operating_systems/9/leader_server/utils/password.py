import bcrypt


def is_same_password(password, salted_hash_password):
    return bcrypt.checkpw(password.encode(), salted_hash_password.encode())


def gen_salted_password(password):
    pwd_bytes = password.encode()
    salt = bcrypt.gensalt()
    return bcrypt.hashpw(pwd_bytes, salt).decode()
