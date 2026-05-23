using System;
using Antmicro.Renode.Peripherals;
using Antmicro.Renode.Peripherals.I2C;
using Antmicro.Renode.Peripherals.Sensor;
using Antmicro.Renode.Logging;

namespace Antmicro.Renode.Peripherals.Sensors
{
    public class INA219 : II2CPeripheral, IPeripheral
    {
        public INA219()
        {
            registers = new byte[256];
            Reset();
        }

        public void Reset()
        {
            Array.Clear(registers, 0, registers.Length);
            registerPointer = 0;

            // Default-ish INA219 behavior
            Write16(REG_CONFIG, 0x399F);     // typical reset config
            Write16(REG_CALIBRATION, 4096);

            BusVoltage = 0f;
            ShuntVoltage = 0f;
            Current = 0f;
            Power = 0f;
        }

        public void Write(byte[] data)
        {
            if(data == null || data.Length == 0)
            {
                return;
            }

            // first byte = register pointer
            registerPointer = data[0];

            if(data.Length == 1)
            {
                return;
            }

            for(int i = 1; i < data.Length; i++)
            {
                registers[registerPointer] = data[i];
                this.Log(LogLevel.Debug, "INA219 Write reg 0x{0:X2} = 0x{1:X2}", registerPointer, data[i]);
                registerPointer++;
            }
        }

        public byte[] Read(int count)
        {
            var result = new byte[count];

            for(int i = 0; i < count; i++)
            {
                result[i] = registers[registerPointer];
                this.Log(LogLevel.Debug, "INA219 Read reg 0x{0:X2} -> 0x{1:X2}", registerPointer, result[i]);
                registerPointer++;
            }

            return result;
        }

        public void FinishTransmission()
        {
        }

        private void Write16(byte reg, ushort value)
        {
            registers[reg] = (byte)((value >> 8) & 0xFF);
            registers[reg + 1] = (byte)(value & 0xFF);
        }

        private ushort Read16(byte reg)
        {
            return (ushort)((registers[reg] << 8) | registers[reg + 1]);
        }

        private void WriteVoltage(byte reg, float value)
        {
            // VERY simplified scaling (good enough for firmware tests)
            ushort raw = (ushort)(value * 100);
            Write16(reg, raw);
        }

        private float ReadVoltage(byte reg)
        {
            return Read16(reg) / 100.0f;
        }

        private const byte REG_CONFIG         = 0x00;
        private const byte REG_SHUNT_VOLTAGE  = 0x01;
        private const byte REG_BUS_VOLTAGE    = 0x02;
        private const byte REG_POWER          = 0x03;
        private const byte REG_CURRENT        = 0x04;
        private const byte REG_CALIBRATION    = 0x05;

        private byte registerPointer;
        private readonly byte[] registers;

        public float BusVoltage
        {
            get => ReadVoltage(REG_BUS_VOLTAGE);
            set => WriteVoltage(REG_BUS_VOLTAGE, value);
        }

        public float ShuntVoltage
        {
            get => ReadVoltage(REG_SHUNT_VOLTAGE);
            set => WriteVoltage(REG_SHUNT_VOLTAGE, value);
        }

        public float Current
        {
            get => ReadVoltage(REG_CURRENT);
            set => WriteVoltage(REG_CURRENT, value);
        }

        public float Power
        {
            get => ReadVoltage(REG_POWER);
            set => WriteVoltage(REG_POWER, value);
        }
    }
}