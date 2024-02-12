#ifndef GarageSpan_H
#define GarageSpan_H

#include "HomeSpan.h"
#include "Config.h"

struct GarageSpan : Service::GarageDoorOpener  {
private:
  // Minimum viable characteristics
  SpanCharacteristic *currentDoorState;
  SpanCharacteristic *targetDoorState;
  SpanCharacteristic *obstructionDetected;

public:
  GarageSpan() : Service::GarageDoorOpener () {
    pinMode(OPEN_LIMIT, INPUT);
    pinMode(CLOSE_LIMIT, INPUT);
    pinMode(OSC, OUTPUT);

    pinMode(STATUS_LED, OUTPUT);
  }

  void begin() {
    homeSpan.enableOTA();
    homeSpan.begin(Category::GarageDoorOpeners, "Garage Door", "GarageDoorOpener");
  }

  boolean update() {
    // Monitor OPEN / CLOSE statuses
    if (digitalRead(OPEN_LIMIT) == HIGH) {
      Serial.println("OPEN_LIMIT triggered");
      this->currentDoorState->setVal(0);
    }

    else if (digitalRead(CLOSE_LIMIT) == HIGH) {
      Serial.println("CLOSE_LIMIT triggered");
      this->currentDoorState->setVal(1);
    }

    else {
      Serial.println("Neither door state is active, defaulting to door OPEN for safety.");
      this->currentDoorState->setVal(0);
    }

    // Trigger door
    if (targetDoorState->updated()) {
      digitalWrite(STATUS_LED, HIGH);
      digitalWrite(OSC, HIGH);
      delay(100);
      digitalWrite(OSC, LOW);
      digitalWrite(STATUS_LED, LOW);
    }
  }
};

#endif