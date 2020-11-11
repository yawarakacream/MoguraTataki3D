#include "Arduino.h"
#include "SegmentDisplay.hpp"

bool SegmentDisplay::NUMBERS[10][7] = {
  /* 0 */ {true, true, true, true, true, true, false},
  /* 1 */ {false, true, true, false, false, false, false},
  /* 2 */ {true, true, false, true, true, false, true},
  /* 3 */ {true, true, true, true, false, false, true},
  /* 4 */ {false, true, true, false, false, true, true},
  /* 5 */ {true, false, true, true, false, true, true},
  /* 6 */ {true, false, true, true, true, true, true},
  /* 7 */ {true, true, true, false, false, true, false},
  /* 8 */ {true, true, true, true, true, true, true},
  /* 9 */ {true, true, true, true, false, true, true},
};

SegmentDisplay::SegmentDisplay(int (&paramPins)[7], bool paramShowZero) : showZero(paramShowZero) {

  memcpy(pins, paramPins, sizeof(paramPins));

  for (int i = 0; i < 7; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }

  setValue(0);

}

void SegmentDisplay::setValue(int value) {
  for (int i = 0; i < 7; i++)
    digitalWrite(pins[i], value == 0 && !showZero ? false : NUMBERS[value][i]);
}

