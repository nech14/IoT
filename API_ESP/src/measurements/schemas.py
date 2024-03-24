
from datetime import datetime
from typing import Union
from pydantic import BaseModel


class TemperatureValue(BaseModel):
    device_id: int
    location: str
    value: float
    timestamp: Union[datetime, None] = None
