import json
import socket
from threading import Thread

from constants import LEADER_HOST, LEADER_PORT, MAX_PAYLOAD_SIZE
from leader_server.handlers.create_post import create_post
from leader_server.handlers.login import login
from leader_server.handlers.view_posts import view_posts

HANDLERS = {
    "login": login,
    "create_post": create_post,
    "view_posts": view_posts,
}


def on_new_client(conn, address):
    with conn:
        print("Listening on: " + str(address))
        try:
            while True:
                data = conn.recv(MAX_PAYLOAD_SIZE)
                if data:
                    msg = json.loads(data.decode())
                    res = HANDLERS[msg["method"]](msg)
                    conn.send(json.dumps(res).encode())
        except Exception as e:
            print("Error: ", address, e.with_traceback(None))


def main():
    with socket.socket() as server:
        server.bind((LEADER_HOST, LEADER_PORT))
        # configure how many client the server can listen simultaneously
        server.listen(100)
        while True:
            sock, address = server.accept()  # accept new connection
            Thread(target=on_new_client, args=(sock, address)).start()


if __name__ == "__main__":
    main()
