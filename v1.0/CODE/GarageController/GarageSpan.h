#ifndef GARAGE_SPAN_H
#define GARAGE_SPAN_H

#include "HomeSpan.h"
#include "Config.h"

class GarageSpan : Service::GarageDoorOpener  {
private:
  // Minimum viable characteristics
  SpanCharacteristic *currentDoorState;
  SpanCharacteristic *targetDoorState;
  SpanCharacteristic *obstructionDetected;

public:
  GarageSpan() : Service::GarageDoorOpener() {
    this->currentDoorState = new Characteristic::CurrentDoorState();
    this->targetDoorState = new Characteristic::TargetDoorState();
    this->obstructionDetected = new Characteristic::ObstructionDetected();

    pinMode(OPEN_LIMIT, INPUT);
    pinMode(CLOSE_LIMIT, INPUT);
    pinMode(OSC, OUTPUT);

    pinMode(STATUS_LED, OUTPUT);
  }

  boolean update() {
    // Trigger door
    if (targetDoorState->updated()) {
      digitalWrite(STATUS_LED, HIGH);
      digitalWrite(OSC, HIGH);
      delay(100);
      digitalWrite(OSC, LOW);
      digitalWrite(STATUS_LED, LOW);
    }

    return true;
  }

  void loop() {
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

    delay(250);
  }
};
#endif