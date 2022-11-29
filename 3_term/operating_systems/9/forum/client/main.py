import pytermgui as ptg

from client.views.login import client_login_form, login


def main():
    with ptg.WindowManager() as ui:
        client_login_form(
            ui,
            login,
        )


if __name__ == "__main__":
    main()
