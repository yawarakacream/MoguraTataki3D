#ifndef PANEL_H_INCLUDED
#define PANEL_H_INCLUDED

#include <CapacitiveSensor.h>

class Panel {

  public:
    Panel(int paramPinSensorInput, int paramPinSensorOutput, int paramPinLED, long paramThreshold);
    void setLED(bool value);
    bool check();
    bool isTarget();
    void setTarget(bool value);
    bool equals(Panel p);

  private:
    static int CS_TIME;
    
    const int pinLED;
    const CapacitiveSensor sensor;
    const long threshold;

    bool target;
    bool lastTouchState = false;

};

#endif

