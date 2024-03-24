from fastapi import APIRouter
from src.measurements.schemas import TemperatureValue
from src import database as db
from decimal import Decimal as dec

router = APIRouter()
db_name = "data/database.db"


@router.get("/location_data")
def get_location_data(location: str):
    data = db.get_location_data(location, db=db_name)
    return {"data": data, "len": len(data)}


@router.get("/location_data/{location}")
def get_location_data(location: str):
    data = db.get_location_data(location, db=db_name)
    return {"data": data, "len": len(data)}


@router.post("/submit_temperature")
def submit_temperature(measurement: TemperatureValue):
    db.adding_data(measurement.device_id, measurement.location, round(measurement.value, 2), measurement.timestamp, db=db_name)
    return {"status": "updated"}
