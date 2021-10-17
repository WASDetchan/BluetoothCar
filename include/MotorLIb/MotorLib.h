// Библиотека для удобного управления моторами

#ifndef motor_h
#define motor_h

#include <Arduino.h>

enum driverType{
    MOTOR_2WIRE,
    MOTOR_3WIRE,
};

class Motor{
private:

    unsigned long _time = millis();
    byte _pin1, _pin2{}, _pin_pwm, _minSpeed = 0, _speed = 0, _changeTimeResolution = 50, _changeSpeed{}, _finalSpeed = 0;
    driverType _type;
    float _k = 1.0;
public:
    Motor(byte pin1, byte pin_pwm);

    __attribute__((unused)) Motor(byte pin1, byte pin2, byte pin_pwm);

    void setMinSpeed(int minSpeed);

    void setChangeTimeResolution(int changeTimeResolution);

    void setMotorSpeed(byte Speed);

    void setMotorSpeedSmooth(byte finalSpeed, int changeTime);

    void updateMotor();
};

#endif