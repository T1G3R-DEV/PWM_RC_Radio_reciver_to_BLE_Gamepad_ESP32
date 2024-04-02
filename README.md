# PWM_RC_Radio_reciver_to_BLE_Gamepad_ESP32
ESP32 project to turn RC PWM rerciver (eg Spectrum AR6115 in my case) to an PC Gamepad (using Arduino IDE)

On the hardware sid you only need to connect your reciver to GND and Power (3.3 or 5V) of your esp Module and each signal output of yor reciver to one digital input of your ESP32. (I have used Pins D15, D16,D17,D18,D19,D21) but you can use any digital input capable pins you like (just change the Pinnumbers int the .ino file). Once everything connected and configured in the .ino file flash it onto the esp. Once you power it up you should be able to connect to it via Bluetooth and your good to go!
