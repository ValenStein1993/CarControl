import struct
import serial
import time
import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtWidgets
from collections import deque

class UartMonitor:
    def __init__(self, ser):
        self.variables = []
        self.data = []
        self.subplots = []
        self.payload_size = 0

        self.ser = ser
        self.read_uart() # get config

    def parse_config(self, payload):
        if self.variables:
            return

        i = 0
        while i < len(payload):
            name_len = payload[i]
            i += 1

            name = payload[i:i+name_len].decode()
            i += name_len

            var_type = payload[i]
            i += 1

            size = payload[i]
            i += 1

            self.variables.append({
                "name": name,
                "type": var_type,
                "size": size
            })

            self.data.append(deque(maxlen=500))

        self.payload_size = sum(v["size"] for v in self.variables)
        print("Config received:", self.variables)

    def parse_data(self, payload):
        i = 0

        for idx, var in enumerate(self.variables):
            raw = payload[i:i+var["size"]]

            if var["type"] == 0:          # e_bool
                value = struct.unpack("<?", raw)[0]

            elif var["type"] == 1:        # e_uint8
                value = struct.unpack("<B", raw)[0]

            elif var["type"] == 2:        # e_int8
                value = struct.unpack("<b", raw)[0]

            elif var["type"] == 3:        # e_uint16
                value = struct.unpack("<H", raw)[0]

            elif var["type"] == 4:        # e_int16
                value = struct.unpack("<h", raw)[0]

            elif var["type"] == 5:        # e_uint32
                value = struct.unpack("<I", raw)[0]

            elif var["type"] == 6:        # e_int32
                value = struct.unpack("<i", raw)[0]

            elif var["type"] == 7:        # e_float
                value = struct.unpack("<f", raw)[0]

            else:
                raise ValueError(f"Unknown type: {var['type']}")
            

            self.data[idx].append(value)
            i += var["size"]

    def read_uart(self):
        while self.ser.in_waiting > 0 or not self.variables:
            if self.ser.read() == b'\xAA':
                if self.ser.read() == b'\x55':
                    packet_type = self.ser.read()[0]

                    if packet_type == 0x01:
                        length = self.ser.read()[0]
                        payload = self.ser.read(length)
                        self.parse_config(payload)

                    elif packet_type == 0x02 and self.payload_size:
                        payload = self.ser.read(self.payload_size)
                        self.parse_data(payload)

    def update_plot(self):
        self.read_uart()

        for idx in range(len(self.variables)):
            self.subplots[idx].setData(list(self.data[idx]))

    def run(self):
        app = QtWidgets.QApplication([])
        win = pg.GraphicsLayoutWidget(show=True)

        for idx, var in enumerate(self.variables):
            plot = win.addPlot(row=idx, col=0)
            plot.setLabel("left", var["name"])
            curve = plot.plot()
            self.subplots.append(curve)

        timer = QtCore.QTimer()
        timer.timeout.connect(self.update_plot)
        timer.start(20)

        app.exec()


if __name__ == "__main__":
    #ser = serial.Serial("COM3", 115200)
    ser = serial.serial_for_url("socket://127.0.0.1:12345")
    um = UartMonitor(ser)
    um.run()