import sqlite3
from datetime import datetime, timezone, timedelta
from tzlocal import get_localzone
import os

name_db = '../data/database.db'


def connect_db(db):
    conn = sqlite3.connect(name_db)
    cursor = conn.cursor()
    return conn, cursor


def create_location_db(db=name_db):
    error = None
    if not os.path.exists(db):
        error = "Didn't find the database"

    conn, cursor = connect_db(db)

    cursor.execute('''
        CREATE TABLE IF NOT EXISTS datas(
            id INTEGER PRIMARY KEY,
            location TEXT,
            data REAL,
            event_time TEXT,
            event_timezone TEXT
        )
    ''')

    if not error is None:
        tz_local = get_localzone()
        current_time_local = datetime.now(tz_local)
        event_data = (error, -1, current_time_local.isoformat(), tz_local.tzname(current_time_local))
        cursor.execute("INSERT INTO datas (location, data, event_time, event_timezone) VALUES (?, ?, ?, ?)",
                       event_data)
        conn.commit()
        conn.close()


def adding_data(location, data, db=name_db):
    if not os.path.exists(db):
        create_location_db()
    conn, cursor = connect_db(db)
    tz_local = get_localzone()
    current_time_local = datetime.now(tz_local)
    event_data = (location, data, current_time_local.isoformat(), tz_local.tzname(current_time_local))
    cursor.execute("INSERT INTO datas (location, data, event_time, event_timezone) VALUES (?, ?, ?, ?)",
                   event_data)
    conn.commit()
    conn.close()


adding_data("home1", 120.142)