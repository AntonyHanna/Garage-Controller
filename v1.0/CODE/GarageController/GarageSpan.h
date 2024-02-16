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

  void pulse_LED(uint8_t pin, int pulses = 1, int cycle_time = 250) {
    for(int i = 0; i < pulses; i++) {
      digitalWrite(pin, HIGH);
      delay(cycle_time / 2);
      digitalWrite(pin, LOW);
      delay(cycle_time / 2);
    }    
  }

public:
  GarageSpan() : Service::GarageDoorOpener() {
    this->currentDoorState = new Characteristic::CurrentDoorState();
    this->targetDoorState = new Characteristic::TargetDoorState();
    this->obstructionDetected = new Characteristic::ObstructionDetected();

    pinMode(OPEN_LIMIT, INPUT);
    pinMode(CLOSE_LIMIT, INPUT);
    pinMode(OSC, OUTPUT);

    pinMode(STATUS_LED, OUTPUT);

    pulse_LED(STATUS_LED, 5);

  }

  boolean update() {
    // Trigger door
    if (targetDoorState->updated()) {
      digitalWrite(OSC, HIGH);
      digitalWrite(OSC, LOW);
      pulse_LED(STATUS_LED);
    }

    return true;
  }

  void loop() {
    // Monitor OPEN / CLOSE statuses
    if (digitalRead(OPEN_LIMIT) == HIGH) {
      Serial.println("OPEN_LIMIT triggered");
      //this->currentDoorState->setVal(0);
    }

    else if (digitalRead(CLOSE_LIMIT) == HIGH) {
      Serial.println("CLOSE_LIMIT triggered");
      //this->currentDoorState->setVal(1);
    }

    else {
      this->currentDoorState->setVal(0);
    }
  }
};
#endif