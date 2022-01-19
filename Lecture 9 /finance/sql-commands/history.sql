CREATE TABLE history(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    stock TEXT NOT NULL,
    shares INTEGER NOT NULL,
    price_per_share NUMERIC NOT NULL,
    transaction_type TEXT NOT NULL,
    Timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    inquirer_id INTEGER,
    FOREIGN KEY (inquirer_id)
      REFERENCES users (id)
         ON DELETE CASCADE
         ON UPDATE NO ACTION);
