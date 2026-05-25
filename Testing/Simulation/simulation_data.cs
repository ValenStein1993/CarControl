using Antmicro.Renode.Core;
using Antmicro.Renode.Peripherals.Bus;
using Antmicro.Renode.Core.Structure.Registers;
using System;

namespace Antmicro.Renode.Peripherals.Simulation
{
    public class SimulationData : BasicDoubleWordPeripheral, IKnownSize
    {
        public SimulationData(Machine machine) : base(machine)
        {
            DefineRegisters();
        }

        private void DefineRegisters()
        {
            Registers.AccelX.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => AccelX = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(AccelX),
                    name: "ACCEL_X");

            Registers.AccelY.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => AccelY = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(AccelY),
                    name: "ACCEL_Y");

            Registers.AccelZ.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => AccelZ = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(AccelZ),
                    name: "ACCEL_Z");

            Registers.GyroX.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => GyroX = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(GyroX),
                    name: "GYRO_X");

            Registers.GyroY.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => GyroY = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(GyroY),
                    name: "GYRO_Y");

            Registers.GyroZ.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => GyroZ = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(GyroZ),
                    name: "GYRO_Z");

            Registers.Current.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => Current = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(Current),
                    name: "CURRENT");

            Registers.Power.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => Power = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(Power),
                    name: "POWER");

            Registers.Angle.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => Angle = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(Angle),
                    name: "ANGLE");

            Registers.AngleSpeed.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => AngleSpeed = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(AngleSpeed),
                    name: "ANGLESPEED");
        }

        // Reinterpret uint bits as float
        private static float ToFloat(ulong v)
        {
            return BitConverter.ToSingle(BitConverter.GetBytes((uint)v), 0);
        }

        // Reinterpret float bits as uint
        private static ulong FromFloat(float v)
        {
            return BitConverter.ToUInt32(BitConverter.GetBytes(v), 0);
        }

        public long Size => 0x1000;

        public float AccelX { get; set; }
        public float AccelY { get; set; }
        public float AccelZ { get; set; }
        public float GyroX { get; set; }
        public float GyroY { get; set; }
        public float GyroZ { get; set; }
        public float Current { get; set; }
        public float Power { get; set; }
        public float Angle { get; set; }
        public float AngleSpeed { get; set; }

        private enum Registers : long
        {
            AccelX     = 0x00,
            AccelY     = 0x04,
            AccelZ     = 0x08,
            GyroX      = 0x0C,
            GyroY      = 0x10,
            GyroZ      = 0x14,
            Current    = 0x18,
            Power      = 0x1C,
            Angle      = 0x20,
            AngleSpeed = 0x24
        }
    }
}