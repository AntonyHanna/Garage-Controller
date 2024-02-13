#include "HomeSpan.h"
#include "GarageSpan.h"

void setup() {
  Serial.begin(115200);
  WiFi.setSleep(false);

  homeSpan.enableOTA();
  homeSpan.begin(Category::GarageDoorOpeners, "Garage Door", "GarageDoorOpener");

  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Name("GarageController");
  new Characteristic::Manufacturer("SpaGET");
  new Characteristic::SerialNumber("gc1.0");
  new Characteristic::Model("ESP32-WROOM");
  new Characteristic::HardwareRevision("1.0");
  new Characteristic::FirmwareRevision("1.0");
  new Characteristic::Identify();
  new Service::HAPProtocolInformation();
  new Characteristic::Version("1.0.0");

  new GarageSpan();
}

void loop() {
  homeSpan.poll();
}
