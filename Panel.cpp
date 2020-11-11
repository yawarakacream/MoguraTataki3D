#include "Arduino.h"

#include "Panel.hpp"

int Panel::CS_TIME = 30;

Panel::Panel(int paramPinSensorInput, int paramPinSensorOutput, int paramPinLED, long paramThreshold) : pinLED(paramPinLED), 
  sensor(CapacitiveSensor(paramPinSensorInput, paramPinSensorOutput)), target(false), threshold(paramThreshold) {

  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);

  sensor.set_CS_AutocaL_Millis(0xffffffff);
  
}

void Panel::setLED(bool value) {
  digitalWrite(pinLED, value);
}

bool Panel::check() {
  
  bool touchState = threshold < sensor.capacitiveSensor(CS_TIME);

  return touchState && touchState != lastTouchState;
  
}

bool Panel::isTarget() {
  return target;
}

void Panel::setTarget(bool value) {
  setLED(target = value);
}

/**
 * LEDのピンで同一パネルか判断する
 */
bool Panel::equals(Panel p) {
  return pinLED == p.pinLED;
}

