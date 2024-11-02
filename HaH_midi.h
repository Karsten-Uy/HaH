enum Mode {
  CH,
  FX
};

// Input Pins with board constants
const int BUT_2 = 1;       // Serial Transmit (TX) - Digital Pin 1
const int BUT_1 = 0;       // Serial Receive (RX) - Digital Pin 0
const int BUT_0 = 2;       // Digital Pin 2
const int BUT_5 = 3;       // Digital Pin 3 / PWM
const int BUT_4 = 4;       // Digital Pin 4
const int BUT_3 = 5;       // Digital Pin 5 / PWM
const int LED_2 = 6;       // Digital Pin 6 / PWM
const int LED_1 = 7;       // Digital Pin 7
const int LED_0 = 8;       // Digital Pin 8
const int LED_3 = 9;       // Digital Pin 9 / PWM
const int LED_4 = 10;      // Digital Pin 10 / PWM
const int LED_5 = 16;      // Digital Pin 16
const int LED_M = 14;     // Digital Pin 14 (Assignment LED_SW)
const int BUT_M = 15;     // Digital Pin 15 (Assignment BUT_SW)

// Analog Pins
const int BUT_D = A0;     // Analog Pin 0 (Assignment BUT_D)
const int LED_D = A1;     // Analog Pin 1 (Assignment LED_D)
const int POT_EX = A3;     // Analog Pin 3 (Assignment EX)

// Other
const int DEBOUNCETIME = 5;
const int DELAY_TAP_LED_TIME = 5;
const int RELEASEVEL = 127;
const int NUM_BUTTONS = 6;

// Array of button pin constants
const int buttonPins[6] = {BUT_0, BUT_1, BUT_2, BUT_3, BUT_4, BUT_5};

// Array of LED pin constants
const int ledPins[6] = {LED_0, LED_1, LED_2, LED_3, LED_4, LED_5};