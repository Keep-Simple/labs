from sqlalchemy import Column, Integer, String
from sqlalchemy.orm import relationship

from leader_server.database import Base
from leader_server.utils.random_string import gen_random_string


class User(Base):
    __tablename__ = "users"

    id = Column(Integer, primary_key=True)
    name = Column(String, unique=True)
    password = Column(String)
    token = Column(
        String,
        index=True,
        unique=True,
        default=gen_random_string,
    )
    posts = relationship("Post", cascade="all", back_populates="user")

    def __repr__(self):
        return "<User(name='%s')>" % (self.name)
