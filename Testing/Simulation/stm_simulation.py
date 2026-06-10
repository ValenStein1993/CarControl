from pathlib import Path
import time
import threading
import sys
from pyrenode3.wrappers import Emulation, Monitor
# the current version of pyrenode3 has an error when loading native DLLs for Windows using clr. Therefore pyrenode3/loader.py has to be adapted to skip loading of native DLLs to avoid BadImageErrors. 

SCRIPT_DIR = Path(__file__).parent

class StmSimulation:
    def __init__(self):
        self.e = Emulation()
        self.m = Monitor()
        self.sim_thread = None

        self.m.execute(f"path add @{SCRIPT_DIR}")
        self.m.execute_script("run_renode.resc")
        self.simdata = self.e.stm32.sysbus.sim
    
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

    def run_simulation(self, input):
        def run_simulation_():
            for timestamp, values in input:
                # Wait until Renode's virtual time reaches the timestamp
                while True:
                    elapsed = self.e.stm32.ElapsedVirtualTime.TimeElapsed.TotalSeconds
                    if elapsed >= timestamp:
                        break
                    time.sleep(0.05)  # Sleep briefly to avoid busy waiting
                
                print(f"Virtual t={elapsed:.2f}s → {values}")
                for key, value in values.items():
                    setattr(self.simdata, key, value)
                    
        self.sim_thread = threading.Thread(target=run_simulation_, daemon=True)
        self.sim_thread.start()



if __name__ == "__main__":
    timeline = [
    (0.0,  {'Angle': 0.0,  'AngleSpeed': 0.0,  'Current': 0.5}),
    (2.0,  {'Angle': 15.0, 'AngleSpeed': 2.5,  'Current': 0.8}),
    (4.0,  {'Angle': 30.0, 'AngleSpeed': 3.0,  'Current': 1.2}),
    (6.0,  {'Angle': 45.0, 'AngleSpeed': 2.0,  'Current': 1.5}),
    (8.0,  {'Angle': 30.0, 'AngleSpeed': -2.0, 'Current': 1.2}),
    (10.0, {'Angle': 0.0,  'AngleSpeed': -3.0, 'Current': 0.5}),
]



