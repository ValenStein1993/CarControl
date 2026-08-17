#include <string>

namespace topics {
const std::string sensorMeasurements = "/sensor/measurements";
const std::string sensorCalibration = "/sensor/calibration";
const std::string motionControl = "/motion_control";
const std::string vehicleState = "/vehicle_state";
const std::string vehicleStateAct = "/vehicle_state_actual";
const std::string histVehicleState = "/hist_vehicle_state";
const std::string histVehicleStateAct = "/hist_vehicle_state_actual";
const std::string nodeState = "/node_state";
const std::string laserScan = "/lidar_scan";
}

namespace vehicleSize {
    const float wheelbase = 0.14;
    const float wheelRadius = 0.015;
}