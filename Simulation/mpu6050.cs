using System;
using Antmicro.Renode.Peripherals;
using Antmicro.Renode.Peripherals.I2C;
using Antmicro.Renode.Peripherals.Sensor;
using Antmicro.Renode.Logging;

namespace Antmicro.Renode.Peripherals.Sensors
{
    // Minimal MPU6050 register-file model:
    // - First byte of a write sets register pointer
    // - Following bytes write sequential registers (auto-increment)
    // - Reads return sequential register values (auto-increment)
    public class MPU6050 : II2CPeripheral, IPeripheral
    {
        public MPU6050()
        {
            registers = new byte[256];
            Reset();
        }

        public void Reset()
        {
            Array.Clear(registers, 0, registers.Length);
            registerPointer = 0;

            // Typical MPU6050 defaults that many drivers expect
            registers[REG_WHO_AM_I] = 0x68;      // WHO_AM_I
            registers[REG_PWR_MGMT_1] = 0x40;    // Sleep=1 after reset (common default)

            // Provide some deterministic sensor output (Accel/Gyro) so firmware has something to read.
            // Accel X/Y/Z (0x3B..0x40), Gyro X/Y/Z (0x43..0x48)
            SetAccelRaw(0, 0, 0); 
            SetGyroRaw(0, 0, 0);
        }

        public void Write(byte[] data)
        {
            if(data == null || data.Length == 0)
            {
                return;
            }

            // First byte is register address (pointer)
            registerPointer = data[0];

            if(data.Length == 1)
            {
                // Only pointer set
                return;
            }

            // Remaining bytes write sequentially
            for(int i = 1; i < data.Length; i++)
            {
                registers[registerPointer] = data[i];
                this.Log(LogLevel.Debug, "Write reg 0x{0:X2} = 0x{1:X2}", registerPointer, data[i]);
                registerPointer++;
            }
        }

        public byte[] Read(int count)
        {
            var result = new byte[count];

            for(int i = 0; i < count; i++)
            {
                result[i] = registers[registerPointer];
                this.Log(LogLevel.Debug, "Read reg 0x{0:X2} -> 0x{1:X2}", registerPointer, result[i]);
                registerPointer++;
            }

            return result;
        }

        public void FinishTransmission()
        {
        }

        // Helpers so you can hardcode test values in Reset() or extend later
        private void SetAccelRaw(short ax, short ay, short az)
        {
            // Accel registers: 0x3B..0x40 big-endian
            Write16(REG_ACCEL_XOUT_H, ax);
            Write16(REG_ACCEL_YOUT_H, ay);
            Write16(REG_ACCEL_ZOUT_H, az);
        }

        private void SetGyroRaw(short gx, short gy, short gz)
        {
            // Gyro registers: 0x43..0x48 big-endian
            Write16(REG_GYRO_XOUT_H, gx);
            Write16(REG_GYRO_YOUT_H, gy);
            Write16(REG_GYRO_ZOUT_H, gz);
        }

        private void Write16(byte regHigh, short value)
        {
            registers[regHigh] = (byte)((value >> 8) & 0xFF);
            registers[regHigh + 1] = (byte)(value & 0xFF);
        }

        private short Read16(byte regHigh)
        {
            return (short)((registers[regHigh] << 8) | registers[regHigh + 1]);
        }

        private byte registerPointer;
        private readonly byte[] registers;

        // Register constants (partial)
        private const byte REG_ACCEL_XOUT_H = 0x3B;
        private const byte REG_ACCEL_YOUT_H = 0x3D;
        private const byte REG_ACCEL_ZOUT_H = 0x3F;

        private const byte REG_GYRO_XOUT_H  = 0x43;
        private const byte REG_GYRO_YOUT_H  = 0x45;
        private const byte REG_GYRO_ZOUT_H  = 0x47;

        private const byte REG_PWR_MGMT_1   = 0x6B;
        private const byte REG_WHO_AM_I     = 0x75;

        public short AccelX
        {
            get => Read16(REG_ACCEL_XOUT_H);
            set => Write16(REG_ACCEL_XOUT_H, value);
        }

        public short AccelY
        {
            get => Read16(REG_ACCEL_YOUT_H);
            set => Write16(REG_ACCEL_YOUT_H, value);
        }

        public short AccelZ
        {
            get => Read16(REG_ACCEL_ZOUT_H);
            set => Write16(REG_ACCEL_ZOUT_H, value);
        }

        public short GyroX
        {
            get => Read16(REG_GYRO_XOUT_H);
            set => Write16(REG_GYRO_XOUT_H, value);
        }

        public short GyroY
        {
            get => Read16(REG_GYRO_YOUT_H);
            set => Write16(REG_GYRO_YOUT_H, value);
        }

        public short GyroZ
        {
            get => Read16(REG_GYRO_ZOUT_H);
            set => Write16(REG_GYRO_ZOUT_H, value);
        }
    }
}