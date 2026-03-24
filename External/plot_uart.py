import struct
import serial
import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtWidgets
from collections import deque


class UartMonitor:
    def __init__(self, port, baud):
        self.variables = []
        self.data = []
        self.subplots = []
        self.ser = serial.Serial(port, baud)

        self.read_uart()

    def parse_config(self, payload):
        if self.variables:
            return
        
        self.variables = []
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

    def parse_data(self, payload):
        i = 0

        for idx, var in enumerate(self.variables):
            raw = payload[i:i+var["size"]]

            if var["type"] == 0:
                value = struct.unpack("<?", raw)[0]
            elif var["type"] == 1:
                value = struct.unpack("<B", raw)[0]
            elif var["type"] == 2:
                value = struct.unpack("<h", raw)[0]  
            elif var["type"] == 3:
                value = struct.unpack("<f", raw)[0]  
            elif var["type"] == 4:
                value = struct.unpack("<h", raw)[0] >> 12
            else:
                value = raw

            self.data[idx].append(value)
            i += var["size"]

    def read_uart(self):
        while True:
            if not self.ser.in_waiting and self.variables:
                return
            
            if self.ser.read() == b'\xAA' and self.ser.read() == b'\x55':
                packet_type = self.ser.read()[0]

                if packet_type == 0x01:
                    length = self.ser.read()[0]
                    payload = self.ser.read(length)
                    self.parse_config(payload)

                elif packet_type == 0x02:
                    payload_size = sum(v["size"] for v in self.variables)
                    payload = self.ser.read(payload_size)
                    self.parse_data(payload)

    def update_plot(self):
        self.read_uart()
        for idx, var in enumerate(self.variables):
            self.subplots[idx].setData(self.data[idx])



    def monitor_uart(self):
        app = QtWidgets.QApplication([])
        win = pg.GraphicsLayoutWidget(show=True)

        for idx, var in enumerate(self.variables):
            plot = win.addPlot(row=idx, col=1, rowspan=len(self.variables), colspan=1)
            curve = plot.plot()
            self.subplots.append(curve)

        timer = QtCore.QTimer()
        timer.timeout.connect(self.update_plot)
        timer.start(20)
        app.exec()

if __name__ == "__main__":
    port = "COM3"
    baud = 115200

    um = UartMonitor(port, baud)
    um.monitor_uart()