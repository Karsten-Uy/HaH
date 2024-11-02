#include "MIDIUSB.h"
#include <Control_Surface.h>

enum Mode {
  MODE_A,
  MODE_B
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
const int BUT_DE = A0;     // Analog Pin 0 (Assignment BUT_DE)
const int LED_DE = A1;     // Analog Pin 1 (Assignment LED_DE)
const int POT_EX = A3;     // Analog Pin 3 (Assignment EX)

// States
bool buttonStates[6];
bool LEDStates[6];

bool delayState;
bool modeState;
currMode;


// Other
const int DEBOUNCETIME = 10;
const int RELEASEVEL = 127;
const int NUM_BUTTONS = 6;

// Array of button pin constants
const int buttonPins[6] = {BUT_0, BUT_1, BUT_2, BUT_3, BUT_4, BUT_5};

// Array of LED pin constants
const int ledPins[6] = {LED_0, LED_1, LED_2, LED_3, LED_4, LED_5};

//-----------------------------------------
// MIDIUSB Functions

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

// Setup function
void setup() {
  Serial.begin(9600);

  // Configure pins based on assignments
  // Digital Outputs for pins with "LED" assignment
  pinMode(LED_2, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_0, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_M, OUTPUT);

  // Digital Inputs for pins with "BUT" assignment
  pinMode(BUT_2, INPUT_PULLUP);
  pinMode(BUT_1, INPUT_PULLUP);
  pinMode(BUT_0, INPUT_PULLUP);
  pinMode(BUT_5, INPUT_PULLUP);
  pinMode(BUT_4, INPUT_PULLUP);
  pinMode(BUT_3, INPUT_PULLUP);
  pinMode(BUT_M, INPUT_PULLUP);

  // Digital Inputs for the Delay LED and button
  pinMode(BUT_DE, INPUT_PULLUP);
  pinMode(LED_DE, OUTPUT);

  // Analog Input for EX assignment
  pinMode(POT_EX, INPUT);

  for (int i = 0; i < 6; i++) {
    buttonStates[i] = false;  // Set each button state to false
    LEDStates[i] = false;
  }

  modeState = false;
  delayState = false;

}

void loop() {

  bool currentState;

  // mode selector
  currentState = digitalRead(BUT_M);

  if (currentState != modeState) {

    delay(DEBOUNCETIME); // Debounce delay

    if (currentState != modeState) {

      if (currentState == LOW) {
        modeState = false;



      } else {
        modeState = true;


        
      }

    }

  }

  // Check each button state
  for (int i = 0; i < NUM_BUTTONS; i++) {
    // Reading the button state from the appropriate pin
    currentState = digitalRead(buttonPins[i]);

    if (currentState != buttonStates[i]) {

      delay(DEBOUNCETIME); // Debounce delay

      if (currentState != buttonStates[i]) {

        if (currentState == LOW) {

          // change the button state
          buttonStates[i] = false;  // Set the button state to pressed

          // toggle LED, allows for TFF behaviour
          LEDStates[i] = !LEDStates[i];

          // Output the pressed button number to the serial monitor
          Serial.print("Button ");
          Serial.print(i);
          Serial.println(" pressed.");
          
        } else {

          // Handle button release
          buttonStates[i] = true; // Set the button state to not pressed
        }

      }
    }

    if (LEDStates[i]) {
      digitalWrite(ledPins[i], HIGH);  // Turn on the corresponding LED
    } else {
      digitalWrite(ledPins[i], LOW);   // Turn off the corresponding LED
    }

  }
   

  
}




