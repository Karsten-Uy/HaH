enum Mode {
  CH,
  FX
};

// Input Pins with board constants
const int BUT_BIN_0 = 0;       // Serial Transmit (TX) - Digital Pin 1
const int BUT_BIN_1 = 1;       // Serial Receive (RX) - Digital Pin 0
const int BUT_BIN_2 = 2;
const int LED_0 = 7;
const int LED_1 = 6;
const int LED_2 = 5;
const int LED_3 = 8;
const int LED_4 = 10;
const int LED_5 = 16;
const int LED_6 = 9;
const int LED_M = 14;     // Digital Pin 14 (Assignment LED_SW)
const int BUT_M = 15;     // Digital Pin 15 (Assignment BUT_SW)
const int BUT_D = 4;     // Analog Pin 0 (Assignment BUT_D)
const int LED_D = 3;     // Analog Pin 1 (Assignment LED_D)

// Analog Pins

const int POT_EX = A0;     // Analog Pin 3 (Assignment EX)
const int POT_0 = A1;     // Analog Pin 3 (Assignment EX)
const int POT_1 = A2;     // Analog Pin 3 (Assignment EX)
const int POT_2 = A3;     // Analog Pin 3 (Assignment EX)

// Other
const int DEBOUNCETIME = 5;
const int BUT_READ_WAIT_TIME = 10;
const int DELAY_TAP_LED_TIME = 5;
const int RELEASEVEL = 127;
const int POT_THRESHOLD = 5;
const int MUTE_HOLD_TIME = 1500;


// Array of LED pin constants
const int ledPins[7] = {LED_0, LED_1, LED_2, LED_3, LED_4, LED_5, LED_6};


// MIDI CC Assignments
const byte POT_CC_EX = 0;
const byte POT_CC_0 = 1;
const byte POT_CC_1 = 2;
const byte POT_CC_2 = 3;

const byte DEL_TAP_CC = 4;
const byte MUTE_CC = 5;

const byte ccValues_FX[7] = { 14, 15, 16, 17, 18, 19, 20 };
const byte ccValues_CH[7] = { 21, 22, 23, 24, 25, 26, 27 };


const byte MIDI_CHANNEL = 0;

