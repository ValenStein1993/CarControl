from Simulation.stm_simulation import StmSimulation
from Monitor.uart_monitor import UartMonitor, wait_connect_for_url

timeline = [
    (0.0,  {'Angle': 0.0,  'AngleSpeed': 0.0,  'Current': 0.5}),
    (2.0,  {'Angle': 15.0, 'AngleSpeed': 2.5,  'Current': 0.8}),
    (4.0,  {'Angle': 30.0, 'AngleSpeed': 3.0,  'Current': 1.2}),
    (6.0,  {'Angle': 45.0, 'AngleSpeed': 2.0,  'Current': 1.5}),
    (8.0,  {'Angle': 30.0, 'AngleSpeed': -2.0, 'Current': 1.2}),
    (30.0, {'Angle': 0.0,  'AngleSpeed': -3.0, 'Current': 0.5}),
]

sim = StmSimulation()
ser = wait_connect_for_url("socket://127.0.0.1:12345")
um = UartMonitor(ser)
sim.run_simulation(timeline)
um.run()
