#include <Wire.h>
#include <Adafruit_INA219.h>
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

// WiFi Credentials
const char SSID[]     = "YOUR_WIFI_SSID";
const char PASS[]     = "YOUR_WIFI_PASSWORD";

// IoT Cloud Device ID and Secret Key (ersätt dessa med dina egna IoT Cloud-uppgifter)
const char DEVICE_KEY[] = "YOUR_DEVICE_KEY";

// INA219 sensor instance
Adafruit_INA219 ina219;

// Cloud variabler
float current_mA;
float busVoltage;
float power_W;

// WiFi inställning för IoT Cloud
void initProperties() {
  ArduinoCloud.addProperty(current_mA, READ, ON_CHANGE);
  ArduinoCloud.addProperty(busVoltage, READ, ON_CHANGE);
  ArduinoCloud.addProperty(power_W, READ, ON_CHANGE);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

void setup() {
  Serial.begin(115200);
  ina219.begin();
  
  // Kontrollera om sensorn är ansluten
  if (!ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1);  // Avbryt om sensorn inte hittas
  }
  
  ina219.setCalibration_32V_2A();  // Kalibrera sensorn för 32V och 2A
  
  // Anslut till Arduino IoT Cloud
  ArduinoCloud.begin(DEVICE_KEY);
  ArduinoCloud.addProperty(current_mA, READ, ON_CHANGE);
  ArduinoCloud.addProperty(busVoltage, READ, ON_CHANGE);
  ArduinoCloud.addProperty(power_W, READ, ON_CHANGE);
  
  // Vänta på uppkoppling till WiFi
  ArduinoCloud.addWiFiConnection(SSID, PASS);
}

void loop() {
  ArduinoCloud.update();  // Uppdatera molnanslutningen
  
  // Läsa och beräkna sensorvärden
  current_mA = ina219.getCurrent_mA();
  busVoltage = ina219.getBusVoltage_V();
  power_W = busVoltage * (current_mA / 1000.0);  // Effekt i watt
  
  // Skriv ut i Serial Monitor för att verifiera värden
  Serial.print("Current (mA): "); Serial.println(current_mA);
  Serial.print("Voltage (V): "); Serial.println(busVoltage);
  Serial.print("Power (W): "); Serial.println(power_W);
  Serial.println("--------");

  delay(1000);  // Skicka data var sekund
}
