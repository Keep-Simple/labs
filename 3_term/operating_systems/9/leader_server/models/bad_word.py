from sqlalchemy import Column, String

from leader_server.database import Base


class BadWord(Base):
    __tablename__ = "bad_words"

    value = Column(String, primary_key=True)

    def __repr__(self):
        return "<BadWord(value='%s')>" % (self.value)
