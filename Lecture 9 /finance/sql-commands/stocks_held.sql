CREATE TABLE stocks_held (
    user_id INTEGER,
    stock TEXT ,
    shares INTEGER NOT NULL,
    PRIMARY KEY (user_id,stock)
    FOREIGN KEY (user_id)
      REFERENCES users (id)
         ON DELETE CASCADE
         ON UPDATE CASCADE);