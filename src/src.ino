
/*

ESP32 project to turn RC PWM rerciver (eg Spectrum AR6115 in my case) to an PC Gamepad (using Atrduino IDE)
https://github.com/T1G3R-DEV/PWM_RC_Radio_reciver_to_BLE_Gamepad_ESP32

using following librarys: 
ESP32-BLE-Gamepad (v0.5.4)
NimBLE-Arduino (v1.4.1)




*/

#include <Arduino.h>
#include <BleGamepad.h>



BleGamepad bleGamepad;

int readChannel(int inputPin, int minRange, int maxRange, int defaultValue){
    int ch = pulseIn(inputPin, HIGH, 30000);
    if (ch < 100) return defaultValue;
    int result=map(ch, 1000, 2000, minRange, maxRange);
    Serial.println("Result of " + String(inputPin) + ": "+String(result));
    return result;
}


void setup()
{
    Serial.begin(115200);

    pinMode(15, INPUT);
    pinMode(16, INPUT);
    pinMode(17, INPUT);
    pinMode(18, INPUT);
    pinMode(19, INPUT);
    pinMode(21, INPUT);

    
    Serial.println("Starting BLE work!");
    BleGamepadConfiguration bleGamepadConfig;
    bleGamepadConfig.setAutoReport(false); // This is true by default
    bleGamepad.begin(&bleGamepadConfig); // Creates a gamepad with 128 buttons, 2 hat switches and x, y, z, rZ, rX, rY and 2 sliders (no simulation controls enabled by default)
    bleGamepad.setAxes(0, 0, 0, 0, 0, 0, 0, 0);

}

int ch0, ch1, ch2, ch3, ch4, ch5;

void loop()
{
    if (bleGamepad.isConnected())
    {
        Serial.println("Gampad connected");
        
        ch0 = readChannel(15, 0, 32767, 0);
        ch1 = readChannel(16, 0, 32767, 0);
        ch2 = readChannel(17, 0, 32767, 0);
        ch3 = readChannel(18, 0, 32767, 0);
        ch4 = readChannel(19, 0, 32767, 0);
        ch5 = readChannel(21, 0, 32767, 0);

        bleGamepad.setAxes(ch0, ch1, ch2, ch3, ch4, ch5, 0, 0);
        bleGamepad.sendReport();
    }
}
