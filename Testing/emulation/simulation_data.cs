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
            Registers.MPU6050_AccelX.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => MPU6050_AccelX = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(MPU6050_AccelX),
                    name: "MPU6050_AccelX");

            Registers.MPU6050_AccelY.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => MPU6050_AccelY = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(MPU6050_AccelY),
                    name: "MPU6050_AccelY");

            Registers.MPU6050_AccelZ.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => MPU6050_AccelZ = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(MPU6050_AccelZ),
                    name: "MPU6050_AccelZ");

            Registers.MPU6050_GyroX.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => MPU6050_GyroX = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(MPU6050_GyroX),
                    name: "MPU6050_GyroX");

            Registers.MPU6050_GyroY.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => MPU6050_GyroY = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(MPU6050_GyroY),
                    name: "MPU6050_GyroY");

            Registers.MPU6050_GyroZ.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => MPU6050_GyroZ = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(MPU6050_GyroZ),
                    name: "MPU6050_GyroZ");

            Registers.INA219_Current.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => INA219_Current = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(INA219_Current),
                    name: "INA219_Current");

            Registers.INA219_Power.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => INA219_Power = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(INA219_Power),
                    name: "INA219_Power");

            Registers.CJMCU103_Angle.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => CJMCU103_Angle = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(CJMCU103_Angle),
                    name: "CJMCU103_Angle");

            Registers.CJMCU103_AngleSpeed.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => CJMCU103_AngleSpeed = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(CJMCU103_AngleSpeed),
                    name: "CJMCU103_AngleSpeed");
            
            Registers.WheelEncoder_RotSpeed.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => WheelEncoder_RotSpeed = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(WheelEncoder_RotSpeed),
                    name: "WheelEncoder_RotSpeed");

            Registers.WheelEncoder_TranslSpeed.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => WheelEncoder_TranslSpeed = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(WheelEncoder_TranslSpeed),
                    name: "WheelEncoder_TranslSpeed");

            Registers.SetSpeed.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => SetSpeed = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(SetSpeed),
                    name: "SetSpeed");

            Registers.SetAngle.Define(this)
                .WithValueField(0, 32,
                    writeCallback: (_, v) => SetAngle = ToFloat(v),
                    valueProviderCallback: _ => FromFloat(SetAngle),
                    name: "SetAngle");
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

        public float MPU6050_AccelX { get; set; }
        public float MPU6050_AccelY { get; set; }
        public float MPU6050_AccelZ { get; set; }
        public float MPU6050_GyroX { get; set; }
        public float MPU6050_GyroY { get; set; }
        public float MPU6050_GyroZ { get; set; }
        public float INA219_Current { get; set; }
        public float INA219_Power { get; set; }
        public float CJMCU103_Angle { get; set; }
        public float CJMCU103_AngleSpeed { get; set; }
        public float WheelEncoder_RotSpeed { get; set; }
        public float WheelEncoder_TranslSpeed { get; set; }
        public float SetSpeed { get; set; }
        public float SetAngle { get; set; }

        private enum Registers : long
        {
            MPU6050_AccelX     = 0x00,
            MPU6050_AccelY     = 0x04,
            MPU6050_AccelZ     = 0x08,
            MPU6050_GyroX      = 0x0C,
            MPU6050_GyroY      = 0x10,
            MPU6050_GyroZ      = 0x14,
            INA219_Current    = 0x18,
            INA219_Power      = 0x1C,
            CJMCU103_Angle      = 0x20,
            CJMCU103_AngleSpeed = 0x24,
            WheelEncoder_RotSpeed = 0x28,
            WheelEncoder_TranslSpeed = 0x2C,
            SetSpeed   = 0x30,
            SetAngle   = 0x34
        }
    }
}