from pathlib import Path
import time
import subprocess
import os
import sys
from pyrenode3.wrappers import Emulation, Monitor
import serial

from uart_logger import UartLogger

SCRIPT_DIR = os.path.join(Path(__file__).parent, "Emulation")

class StmSimulation:
    def __init__(self):
        self.e = Emulation()
        self.m = Monitor()
        
        self.m.execute(f"path add @{SCRIPT_DIR}")
        self.m.execute_script("run_renode.resc")
        self.simdata = self.e.stm32.sysbus.sim
        
        ser = serial.serial_for_url("socket://127.0.0.1:12345")
        self.uart_logger = UartLogger(ser, plot=True, log=True)

    def update(self):
        self.m.execute("emulation RunFor '0.1'")
        self.uart_logger.update()

    def set_sensor_data(self, sensor_data):
        for key, value in sensor_data.items():
            setattr(self.simdata, key, value)     

    def get_actuator_data(self):
        return {
            'SetSpeed': self.simdata.SetSpeed,
            'SetAngle': self.simdata.SetAngle,
        }





