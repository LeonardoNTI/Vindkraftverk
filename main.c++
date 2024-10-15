#include <Wire.h>
#include <Adafruit_INA219.h>

// Create INA219 instance
Adafruit_INA219 ina219;

// Define variables to store measurements (these will be sent to the Arduino Cloud later)
float current_mA = 0;
float busVoltage = 0;
float power_W = 0;

void setup() {
  Serial.begin(115200); // Initialize serial communication for debugging (optional)

  // Initialize the INA219 sensor
  if (!ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1);  // Halt program if sensor is not found
  }

  // Optional: Calibrate the INA219 sensor
  ina219.setCalibration_32V_2A();

  // **TODO**: Setup Arduino IoT Cloud
  // Write the code to connect your Arduino to the Arduino IoT Cloud here
  // Use Arduino Cloud IoT libraries to define cloud variables (current, voltage, power)
  // Example: ArduinoCloud.addProperty(current_mA, READ, 1 * SECONDS);

  // **TODO**: Setup WiFi connection
  // Connect to WiFi network (SSID and password)
  // Example: ArduinoCloud.begin(SSID, PASSWORD);
}

void loop() {
  // Measure current (in milliamps) drawn by the motor
  current_mA = ina219.getCurrent_mA();

  // Measure voltage (in volts) across the motor
  busVoltage = ina219.getBusVoltage_V();

  // Calculate power (in watts) drawn by the motor
  power_W = busVoltage * (current_mA / 1000.0);  // Convert mA to A

  // **TODO**: Send data to Arduino IoT Cloud
  // Send the measured values to the cloud variables
  // Example: cloud_variable_current = current_mA;
  //          cloud_variable_voltage = busVoltage;
  //          cloud_variable_power = power_W;

  // **Optional**: If you want to log or debug data locally, you can print it
  Serial.print("Current (mA): "); Serial.println(current_mA);
  Serial.print("Voltage (V): "); Serial.println(busVoltage);
  Serial.print("Power (W): "); Serial.println(power_W);
  Serial.println("--------");

  // **TODO**: Delay or adjust the loop frequency if needed
  // You may want to control how frequently the data is sent to the cloud.
  // Example: delay(1000); // Send every 1 second
}
