import os
import struct
import serial
import argparse
import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtWidgets
from collections import deque
from datetime import datetime


class UartLogger:
    def __init__(self, ser, plot=False, log=False):
        self.variables = []
        self.data = []
        self.subplots = []
        self.payload_size = 0
        self.win = None

        self.plot_data = plot
        self.log_data = log
        self.plot_ready = False
        self.log_ready = False
        self.ser = ser
        self.app = QtWidgets.QApplication([])
        self.filename = os.path.join("./logs", datetime.now().strftime(r"uart_log_%Y%m%d_%H%M%S.csv"))

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

    def read_bytes(self):
        success = False
        while self.ser.in_waiting > 0:
            if self.ser.read() == b'\xAA':
                if self.ser.read() == b'\x55':
                    packet_type = self.ser.read()[0]

                    # if package is config and no variables have been received yet, read the config
                    if packet_type == 0x01 and not self.payload_size:
                        length = self.ser.read()[0]
                        payload = self.ser.read(length)
                        self.parse_config(payload)
                        success = True

                    # if package is data and variables have been received, read the data
                    elif packet_type == 0x02 and self.payload_size:
                        payload = self.ser.read(self.payload_size)
                        self.parse_data(payload)
                        success = True
        return success

    def update(self):
        self.read_bytes()
        hasData = all(len(d) != 0 for d in self.data)

        if self.plot_data:
            if (not self.plot_ready) and self.variables:
                self.init_plot()
                self.plot_ready = True
            elif self.plot_ready and hasData:
                self.update_plot()
                self.app.processEvents()
        
        if self.log_data:
            if (not self.log_ready) and self.variables:
                self.init_log()
                self.log_ready = True
            elif self.log_ready and hasData:
                self.update_log()

    def init_plot(self):
        self.win = pg.GraphicsLayoutWidget()
        cols = 1 if len(self.variables) < 4 else 2
        for idx, var in enumerate(self.variables):
            row = idx // cols
            col = idx % cols
            plot = self.win.addPlot(row=row, col=col)
            plot.setLabel("left", var["name"])
            curve = plot.plot()
            self.subplots.append(curve)
        self.win.show()

    def init_log(self):
        os.makedirs(os.path.dirname(self.filename), exist_ok=True)
        with open(self.filename, "w") as f:
            f.write(",".join(v["name"] for v in self.variables) + "\n")

    def update_plot(self):
        for idx in range(len(self.variables)):
            self.subplots[idx].setData(list(self.data[idx]))

    def update_log(self):
        with open(self.filename, "a") as f:
            row = []
            for var_data in self.data:
                row.append(str(var_data[-1]))
            f.write(",".join(row) + "\n")

    def monitor(self):
        timer = QtCore.QTimer()
        timer.timeout.connect(self.update)
        timer.start(100)

        self.app.exec()


if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument("type", type=str, default="serial", choices=["socket", "serial"])
    parser.add_argument("port", type=int, default=3)
    parser.add_argument("--plot", action="store_true")
    parser.add_argument("--log", action="store_true")
    args = parser.parse_args()

    if args.type == "socket":
        ser = serial.serial_for_url(f"socket://127.0.0.1:{args.port}")
    elif args.type == "serial":
        ser = serial.Serial(f"COM{args.port}", 115200)
    else:
        raise ValueError("Unknown type. Use 'socket' or 'serial'.") 
    
    um = UartLogger(ser, args.plot, args.log)
    um.monitor()