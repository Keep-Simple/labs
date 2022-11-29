import json
import socket

from constants import LEADER_HOST, LEADER_PORT, MAX_PAYLOAD_SIZE


class SocketClient:
    def __init__(self):
        self.client_token = None
        self.client = socket.socket()
        self.client.connect((LEADER_HOST, LEADER_PORT))

    def set_token(self, token):
        self.client_token = token

    def get_token(self):
        return self.client_token

    def send_request(self, method, payload, ui):
        self.client.send(
            json.dumps(
                {
                    "auth": {"token": self.client_token},
                    "method": method,
                    "payload": payload,
                }
            ).encode()
        )
        raw_res = self.client.recv(MAX_PAYLOAD_SIZE)
        res = json.loads(raw_res.decode())
        message = res["message"]

        match res["type"]:
            case "error":
                ui.toast(
                    f"[bold red]{message}",
                    delay=6 * 10**3,
                    slot="Alert",
                    animate=False,
                )
                return None
            case "ok":
                ui.toast(
                    f"[bold green]{message}",
                    delay=6 * 10**3,
                    slot="Alert",
                    animate=False,
                )

                return res["payload"]


socket_client = SocketClient()
