import serial
import math

from Simulation.stm_simulation import StmSimulation
from Monitor.uart_monitor import UartMonitor

from gz.sim import TestFixture
from gz.transport import Node
from gz.msgs.stringmsg_pb2 import StringMsg
from gz.msgs.imu_pb2 import IMU
from gz.msgs.twist_pb2 import Twist

WHEEL_BASE = 1.08

class CarSimulation:
    def __init__(self):

        self.sensor_data = {
            'MPU6050_AccelX': 0,
            'MPU6050_AccelY': 0,
            'MPU6050_AccelZ': 0,
            'MPU6050_GyroX': 0,
            'MPU6050_GyroY': 0,
            'MPU6050_GyroZ': 0,
            'INA219_Current': 0,
            'INA219_Power': 0,
            'CJMCU103_Angle': 0,
            'CJMCU103_AngleSpeed': 0,
            'WheelEncoder_RotSpeed': 0,
            'WheelEncoder_TranslSpeed': 0,
        }

        # setup Gazebo simulation
        self.simmodel = TestFixture('./Simulation/Model/carmodel.sdf')
        self.node = Node()
        self.node.subscribe(IMU, "/imu", self.get_imu_data)
        self.pub_actr = self.node.advertise("/cmd_vel", Twist)
        self.simmodel.on_pre_update(self.on_pre_update_cb)

        self.simmodel.finalize()
        self.server = self.simmodel.server()

        # setup Renode simulation
        self.stmsim = StmSimulation()

    def run(self):
        self.server.run(True, 1000, False)

    def on_pre_update_cb(self, info, ecm):
        self.stmsim.set_sensor_data(self.sensor_data)
        self.stmsim.run()
        actr_data = self.stmsim.get_actuator_data()
        self.set_actr_data(actr_data)

    def get_imu_data(self, msg):
        self.sensor_data['MPU6050_AccelX'] = msg.linear_acceleration.x
        self.sensor_data['MPU6050_AccelY'] = msg.linear_acceleration.y
        self.sensor_data['MPU6050_AccelZ'] = msg.linear_acceleration.z

    def set_actr_data(self, actr_data):
        speed = actr_data['SetSpeed']
        angle = actr_data['SetAngle']

        yaw_rate = speed * math.tan(angle) / WHEEL_BASE
        
        msg = Twist()
        msg.linear.x  = speed
        msg.angular.z = yaw_rate
        self.pub_actr.publish(msg)



    


