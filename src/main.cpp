#include <Arduino.h>
#include <SoftwareSerial.h>
#include <MotorLib.h>

#define RX_PIN 2
#define TX_PIN 3
#define MOTOR_A_IN1_PIN
#define MOTOR_A_IN2_PIN
#define MOTOR_A_PWM_PIN

char InputChar = 0;
String InputString = "";
boolean IsInput = false;

SoftwareSerial BTSerial(RX_PIN, TX_PIN); // Bluetooth serial

void setup() {
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);

    Serial.begin(9600);
    BTSerial.begin(38400);

    Serial.println("READY");
    while (InputString != "START") {
        if (BTSerial.available() && InputChar != '\n') {
            Serial.println(InputChar);
            InputChar = (char)BTSerial.read();
            InputString += InputChar;
        }
        if (InputChar == '\n') {
            if (InputString != "START") {
                InputString = "";
            }
            InputChar = 0;
        }
    }
    InputString = "";
    Serial.println("STARTED");
}

void loop(){
    // Bluetooth
    if (BTSerial.available()) { // Sending bluetooth input to serial
        InputChar = (char)BTSerial.read();
        /*if (!(InputString == "" && InputChar == '\n')){
          Serial.write(InputChar);
        }*/
        if (InputChar != '\n') {
            InputString += InputChar;
        }
        else if (InputString != "" && InputChar == '\n') {
            Serial.print("Input: ");
            Serial.println(InputString);
            IsInput = true;
        }
    }

    if (Serial.available()) {
        InputChar = (char)Serial.read(); // Sending serial input to bluetooth (disabled)
        BTSerial.write(InputChar);
        Serial.write(InputChar);
    }

    if (IsInput){

    }
}