import json
import socket
from threading import Thread

from sqlalchemy import create_engine, delete
from sqlalchemy.orm import Session

from constants import (DEFAULT_BAD_WORDS, LEADER_HOST, LEADER_PORT,
                       MAX_PAYLOAD_SIZE)
from leader_server.database import Base
from leader_server.handlers.create_post import create_post
from leader_server.handlers.login import login
from leader_server.handlers.view_posts import view_posts
from leader_server.models.bad_word import BadWord
from leader_server.models.post import Post
from leader_server.models.user import User

HANDLERS = {
    "login": login,
    "create_post": create_post,
    "view_posts": view_posts,
}


def init_db_engine():
    engine = create_engine("sqlite:///db.sqlite", echo=True)
    engine.connect()
    Base.metadata.create_all(engine)
    return engine


def seed_data(db):
    db.execute(delete(BadWord).where())
    db.execute(delete(User).where())
    db.execute(delete(Post).where())
    db.add_all([BadWord(value=bad_word) for bad_word in DEFAULT_BAD_WORDS])
    db.commit()


def on_new_client(engine, conn, address):
    with Session(engine) as db:
        # seed_data(db)
        with conn:
            print("Listening on: " + str(address))
            try:
                while True:
                    data = conn.recv(MAX_PAYLOAD_SIZE)
                    if data:
                        msg = json.loads(data.decode())
                        res = HANDLERS[msg["method"]](db, msg)
                        conn.send(json.dumps(res).encode())
            except Exception as e:
                print("Error: ", address, e.with_traceback(None))


def main():
    engine = init_db_engine()
    with socket.socket() as server:
        server.bind((LEADER_HOST, LEADER_PORT))
        # configure how many client the server can listen simultaneously
        server.listen(100)
        while True:
            sock, address = server.accept()  # accept new connection
            Thread(target=on_new_client, args=(engine, sock, address)).start()


if __name__ == "__main__":
    main()
