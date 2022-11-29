from sqlalchemy import Column, ForeignKey, Integer, String
from sqlalchemy.orm import relationship

from leader_server.database import Base


class Post(Base):
    __tablename__ = "posts"

    id = Column(Integer, primary_key=True)
    content = Column(String)
    user_id = Column(Integer, ForeignKey("users.id"))
    user = relationship("User", back_populates="posts")

    def __repr__(self):
        return "<Post(content='%s')>" % (self.content)
