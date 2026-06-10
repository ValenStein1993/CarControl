import serial
from Simulation.car_simulation import CarSimulation

# concept: 
# start emulation: get Sensor values from Gazebo --> feed into model 
# retrieve setSpeed and setAngle --> feedback to Gazebo

sim = CarSimulation()

sim.run()