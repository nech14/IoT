from fastapi import APIRouter
from src.measurements.schemas import TemperatureValue
from src import database as db

router = APIRouter()
db_name = "data/database.db"


@router.get("/location_data")
def get_location_data(location: str):
    return {"data": db.get_location_data(location, db=db_name)}


@router.get("/location_data/{location}")
def get_location_data(location: str):
    return {"data": db.get_location_data(location, db=db_name)}


@router.post("/submit_temperature")
def submit_temperature(measurement: TemperatureValue):
    db.adding_data(measurement.device_id, measurement.location, measurement.value, measurement.timestamp, db=db_name)
    return {"status": "updated"}
