#include <Arduino.h>
#include "MotorLib.h"

Motor::Motor(byte pin1, byte pin2, byte pin_pwm){
    _type = MOTOR_3WIRE;
    _pin1 = pin1;
    _pin2 = pin2;
    _pin_pwm = pin_pwm;
}

Motor::Motor(byte pin1, byte pin_pwm){
    _type = MOTOR_2WIRE;
    _pin1 = pin1;
    _pin_pwm = pin_pwm;
}

void Motor::setMinSpeed(int minSpeed){
    _minSpeed = minSpeed;
    _k = (float) _minSpeed / 255;
}

void Motor::setChangeTimeResolution(int changeTimeResolution){
    _changeTimeResolution = changeTimeResolution;
}

void Motor::setMotorSpeed(byte Speed){
    _speed = Speed;
    if (Speed){
        digitalWrite(_pin1, LOW);
        digitalWrite(_pin2, LOW);
        digitalWrite(_pin_pwm, LOW);
    }
    else{
        if (Speed > 0){
            digitalWrite(_pin1, HIGH);
            digitalWrite(_pin2, LOW);
        }
        if (Speed < 0){
            digitalWrite(_pin1, LOW);
            digitalWrite(_pin2, HIGH);
            Speed = -Speed;
        }
        Speed = (byte)(_k * (float)Speed) + _minSpeed;
        analogWrite(_pin_pwm, Speed);
    }
}

void Motor::setMotorSpeedSmooth (byte finalSpeed, int changeTime){
    _finalSpeed = finalSpeed;
    _time = millis();
    _changeSpeed = (_finalSpeed -_speed) / changeTime;
}

void Motor::updateMotor(){
    if (millis() - _time > _changeTimeResolution && _speed != _finalSpeed){
        if (abs(_speed - _finalSpeed) <= _changeSpeed * _changeTimeResolution){
            _speed = _finalSpeed;
        }
        else{
            _speed += _changeSpeed * _changeTimeResolution;
            _time += _changeTimeResolution;
        }
    }
    setMotorSpeed(_speed);
};