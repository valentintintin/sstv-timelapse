#ifndef SSTV_TIMELAPSE_ENGINE_H
#define SSTV_TIMELAPSE_ENGINE_H

#include <Arduino.h>

class Engine;

enum COMMAND {
    GET_VOLTAGE,
    GET_TEMPERATURE,
    GET_DRA,
    GET_BUTTON,
    SET_WAKEUP_HOUR,
    SET_WAKEUP_MINUTE,
    SLEEP,
    SET_PTT_ON,
    SET_PTT_OFF,
    SET_FREQ_APRS,
    SET_FREQ_SSTV
};

#include "Communication.h"
#include "DRA.h"
#include "Sleep.h"

class Engine {

public:
    enum STATE {
        PI_STOPPED, PI_STOPPING, PI_RUNNING
    };

    Engine(byte raspberryPin, float freqAprs, float freqSstv, DRA *dra);

    void init(int slaveAddress, byte wakeUpButtonPin, byte wakeUpRtcPin, RtcDS3231<TwoWire> *rtc,
              bool canUseForEver = false);

    void loop();

    int computeCommand(COMMAND command, int data);

private:
    void startPi();

    void stopPi();

    byte raspberryPin;
    STATE state = PI_STOPPED;
    float freqAprs;
    float freqSstv;

    DRA *dra;
};


#endif //SSTV_TIMELAPSE_ENGINE_H