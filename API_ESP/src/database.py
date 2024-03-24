import sqlite3
from datetime import datetime, timezone, timedelta
from tzlocal import get_localzone
import os

name_db = '../data/database.db'


def connect_db(db=name_db):
    conn = sqlite3.connect(db)
    cursor = conn.cursor()
    return conn, cursor


def create_location_db(db=name_db, error=None):
    if not os.path.exists(db):
        error = "Didn't find the database"

    conn, cursor = connect_db(db)

    cursor.execute('''
        CREATE TABLE IF NOT EXISTS datas(
            id INTEGER PRIMARY KEY,
            device_id INTEGER,
            location TEXT,
            value REAL,
            timestamp TEXT
        )
    ''')

    if not error is None:
        event_data = (-1, error, -1, str(datetime.now()))
        cursor.execute("INSERT INTO datas (device_id, location, value, timestamp) VALUES (?, ?, ?, ?)",
                       event_data)
        conn.commit()
        conn.close()


def get_location_data(location, db=name_db):
    if not os.path.exists(db):
        create_location_db(db=db)

    conn, cursor = connect_db(db)

    print(f"{location}")
    cursor.execute(f'SELECT value FROM datas WHERE location == "{location}"')

    rows = cursor.fetchall()

    conn.close()

    return rows


def adding_data(device_id, location, data, timestamp=None, db=name_db):
    if not os.path.exists(db):
        create_location_db(db=db)
    conn, cursor = connect_db(db)
    if timestamp is None:
        timestamp = datetime.now()
    event_data = (device_id, location, data, str(timestamp))
    cursor.execute("INSERT INTO datas (device_id, location, value, timestamp) VALUES (?, ?, ?, ?)",
                   event_data)
    conn.commit()
    conn.close()

#adding_data(1, "fdesfsd", -2)
