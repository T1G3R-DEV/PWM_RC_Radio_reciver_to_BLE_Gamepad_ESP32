
/*

ESP32 project to turn RC PWM rerciver (eg Spectrum AR6115 in my case) to an PC Gamepad (using Arduino IDE)
https://github.com/T1G3R-DEV/PWM_RC_Radio_reciver_to_BLE_Gamepad_ESP32

using following librarys: 
ESP32-BLE-Gamepad (v0.5.4)
NimBLE-Arduino (v1.4.1)

1-8 axes


*/

#include <Arduino.h>
#include <BleGamepad.h>

const int ch_pins[8] = {15, 16, 17, 18, 19, 21, 0,0};
//im using a slightly higher range to fully use the available range 
#define MIN_DURATION 800    //minimum duration of the pwm (when stick is at fully down) (900 us for spectrum recivers)
#define MAX_DURATION 2200   //maximum duration of pwm (2100 us for spectrum recivers)

BleGamepad bleGamepad;

int readChannel(int inputPin, int minRange, int maxRange, int defaultValue){
    int ch = pulseIn(inputPin, HIGH, 30000);
    if (ch < 1) return defaultValue;
    int result=map(ch, MIN_DURATION, MAX_DURATION, minRange, maxRange); //min and max Range are for the output side of things eq ble controller takes values from 0 to 32767
    Serial.println("Result of " + String(inputPin) + ": "+String(result));
    return result;
}


void setup()
{
    Serial.begin(115200);
    for (int pin : ch_pins) 
    {
      pinMode(pin, INPUT);
    }
  
    Serial.println("Starting BLE work!");
    BleGamepadConfiguration bleGamepadConfig;
    bleGamepadConfig.setAutoReport(false); // This is true by default
    bleGamepad.begin(&bleGamepadConfig); // Creates a gamepad with 128 buttons, 2 hat switches and x, y, z, rZ, rX, rY and 2 sliders (no simulation controls enabled by default)
    bleGamepad.setAxes(0, 0, 0, 0, 0, 0, 0, 0);

}

int ch_values[8];

void loop()
{
    if (bleGamepad.isConnected())
    {
        Serial.println("Gampad connected");
        for (int i=0; i<8; i++) 
        {
            ch_values[i] = readChannel(ch_pins[i], 0, 32767, 0);
        }
        bleGamepad.setAxes(ch_values[0], ch_values[1], ch_values[2], ch_values[3], ch_values[4], ch_values[5], ch_values[6], ch_values[7]);
        bleGamepad.sendReport();
    }
}
