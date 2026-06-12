from pathlib import Path
import time
import subprocess
import os
import sys
from pyrenode3.wrappers import Emulation, Monitor

from uart_logger import UartLogger

SCRIPT_DIR = os.path.join(Path(__file__).parent, "Emulation")

class StmSimulation:
    def __init__(self):
        self.e = Emulation()
        self.m = Monitor()
        
        self.m.execute(f"path add @{SCRIPT_DIR}")
        self.m.execute_script("run_renode.resc")
        self.simdata = self.e.stm32.sysbus.sim
        
        self.uart_proc = subprocess.Popen(
                [sys.executable, "uart_logger.py", "socket", "12345"],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )

    
    def run(self):
        self.m.execute("emulation RunFor '0.1'")

    def set_sensor_data(self, sensor_data):
        for key, value in sensor_data.items():
            setattr(self.simdata, key, value)     

    def get_actuator_data(self):
        return {
            'SetSpeed': self.simdata.SetSpeed,
            'SetAngle': self.simdata.SetAngle,
        }





