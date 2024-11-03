#include "MIDIUSB.h"
#include <Control_Surface.h>
#include "HaH_midi.h"

/*******************/
// GLOBAL VARIABLES
/*******************/

Mode currMode;

// States
bool LEDStates[7];

bool delayState;
bool modeState = false; // Flag to track if button press was detected

int lastPotValueEx = -1;
int lastPotValue0 = -1;
int lastPotValue1 = -1;
int lastPotValue2 = -1;
bool lastButRead[3] = {0, 0, 0};

bool butRead[3];

//-----------------------------------------
// MIDIUSB Functions

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush();
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
}

// Setup function
void setup() {
  Serial.begin(9600);

  // Configure pins based on assignments
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
  pinMode(LED_M, OUTPUT);
  pinMode(LED_D, OUTPUT);

  pinMode(BUT_BIN_0, INPUT);
  pinMode(BUT_BIN_1, INPUT);
  pinMode(BUT_BIN_2, INPUT);
  pinMode(BUT_M, INPUT_PULLUP);
  pinMode(BUT_D, INPUT_PULLUP);
  
  pinMode(POT_EX, INPUT);
  pinMode(POT_0, INPUT);
  pinMode(POT_1, INPUT);
  pinMode(POT_2, INPUT);

  for (int i = 0; i < sizeof(LEDStates) / sizeof(LEDStates[0]); i++) {
    LEDStates[i] = false;
  }

  for (int i = 0; i < sizeof(butRead) / sizeof(butRead); i++) {
    butRead[i] = false;
  }

  delayState = false;

  modeState = false;
  digitalWrite(LED_M, LOW);

  currMode = FX;
}

void loop() {

  bool currentState;

  /************************/
  // MODE SELECTOR
  /************************/



  currentState = digitalRead(BUT_M);

  // Check for button press and release
  if (currentState == LOW && !modeState) { // Button is pressed (assuming LOW is pressed)
      delay(DEBOUNCETIME); // Debounce delay

      if (digitalRead(BUT_M) == LOW) { // Confirm the button is still pressed after debounce
          modeState = true; // Set flag to indicate button is currently pressed

          //------------------------------
          // RESETS - Pre Switch

          switch (currMode) { // this runs before any processing for that mode
          case FX:
              for (int i = 0; i < sizeof(LEDStates) / sizeof(LEDStates[0]); i++) { // turn all channels off
                  controlChange(MIDI_CHANNEL, ccValues_FX[i], 0);
              }
              break;

          case CH:
              for (int i = 0; i < sizeof(LEDStates) / sizeof(LEDStates[0]); i++) { // turn all channels off
                  controlChange(MIDI_CHANNEL, ccValues_CH[i], 0);
              }
              break;

          default:
              break;
          }

          // Change mode (T flip-flop behavior)
          currMode = static_cast<Mode>((currMode + 1) % 2); // Cycle through modes
          Serial.print("Current Mode: MODE_");
          Serial.println(static_cast<int>(currMode)); // Print the current mode number

          //---------------------------
          // RESETS - Post Switch

          switch (currMode) { // this runs after switching modes
          case FX:
              for (int i = 0; i < sizeof(LEDStates) / sizeof(LEDStates[0]); i++) {
                  LEDStates[i] = false;
              }
              digitalWrite(LED_M, HIGH);
              break;

          case CH:
              for (int i = 0; i < sizeof(LEDStates) / sizeof(LEDStates[0]); i++) {
                  LEDStates[i] = false;
              }
              LEDStates[0] = true; // Let 1 channel through
              digitalWrite(LED_M, LOW);
              break;

          default:
              break;
          }
      }

  } else if (currentState == HIGH && modeState) {
      // Button released
      modeState = false; // Reset flag for next press
  }


  

  butRead[0] = digitalRead(BUT_BIN_0);
  butRead[1] = digitalRead(BUT_BIN_1);
  butRead[2] = digitalRead(BUT_BIN_2);

  //--------------------------------------
  // CONTROL BUTTONS FX

  // Check for a change from 0 to 1 (button press)
  if ((butRead[0] && !lastButRead[0]) || (butRead[1] && !lastButRead[1]) || (butRead[2] && !lastButRead[2])) {
    
    delay(BUT_READ_WAIT_TIME); // Debounce delay

    // Re-read to confirm the button is still pressed
    butRead[0] = digitalRead(BUT_BIN_0);
    butRead[1] = digitalRead(BUT_BIN_1);
    butRead[2] = digitalRead(BUT_BIN_2);

    if (butRead[0] || butRead[1] || butRead[2]) {
      // Calculate decimal value from binary state
      int numBut = ((butRead[2] << 2) | (butRead[1] << 1) | butRead[0]) - 1;

      switch (currMode) {

      case FX:

        // Toggle the LED state for the button
        LEDStates[numBut] = !LEDStates[numBut];

        controlChange(MIDI_CHANNEL, ccValues_FX[numBut], LEDStates[numBut] ? 0 : 127);

        break;

      case CH:

        for (int i = 0; i < sizeof(LEDStates) / sizeof(LEDStates[0]); i++) {

          if (i == numBut) {
            controlChange(MIDI_CHANNEL, ccValues_CH[i], 127);
            LEDStates[i] = true;
          } else {
            controlChange(MIDI_CHANNEL, ccValues_CH[i], 0);
            LEDStates[i] = false;
          }

        }

        break;

      default: // shouldn't happen but is here anyways
        break;
      }


      // Send MIDI Control Change message based on LED state
      

      // Output the button number to the serial monitor
      Serial.print("Button ");
      Serial.print(numBut);
      Serial.println(" pressed.");
    }
  }


  // Update the last known states for the next loop iteration
  lastButRead[0] = butRead[0];
  lastButRead[1] = butRead[1];
  lastButRead[2] = butRead[2];

  for (int i = 0; i < sizeof(ledPins) / sizeof(ledPins[0]); i++) {

    // CONTROL BUTTONS LEDs
    if (LEDStates[i]) {
      digitalWrite(ledPins[i], HIGH);  // Turn on the corresponding LED
    } else {
      digitalWrite(ledPins[i], LOW);   // Turn off the corresponding LED
    }
  }

  /************************/
  // DELAY TAPPER
  /************************/

  currentState = digitalRead(BUT_D);
  if (currentState != delayState) {
    delay(DEBOUNCETIME); // Debounce delay

    if (currentState != delayState) {
      if (currentState == LOW) {

        Serial.print("Current Mode: Delay Tapped");

        controlChange(MIDI_CHANNEL, CC_MIDI_MODULATION, 127);
        digitalWrite(LED_D, HIGH);  // Turn on the corresponding LED

        delay(DELAY_TAP_LED_TIME);
        
        digitalWrite(LED_D, LOW);  // Turn off the corresponding LED
        controlChange(MIDI_CHANNEL, CC_MIDI_MODULATION, 0);

      } 
      delayState = currentState; // Update the mode state
    }
  }

  /************************/
  // POTENTIOMETER READ
  /************************/

  /************************/
  // POTENTIOMETER READS
  /************************/

  // Read each potentiometer and send MIDI CC if the value has changed

  // Potentiometer EX
  int potValueEx = analogRead(POT_EX);
  byte ccValueEx = map(potValueEx, 0, 1023, 0, 127);
  if (abs(potValueEx - lastPotValueEx) > POT_THRESHOLD) {
    controlChange(MIDI_CHANNEL, POT_CC_EX, ccValueEx);
    Serial.print("Pot EX Value: ");
    Serial.println(ccValueEx);
    lastPotValueEx = potValueEx;
  }

  // Potentiometer 0
  int potValue0 = analogRead(POT_0);
  byte ccValue0 = map(potValue0, 0, 1023, 0, 127);
  if (abs(potValue0 - lastPotValue0) > POT_THRESHOLD) {
    controlChange(MIDI_CHANNEL, POT_CC_0, ccValue0);
    Serial.print("Pot 0 Value: ");
    Serial.println(ccValue0);
    lastPotValue0 = potValue0;
  }

  // Potentiometer 1
  int potValue1 = analogRead(POT_1);
  byte ccValue1 = map(potValue1, 0, 1023, 0, 127);
  if (abs(potValue1 - lastPotValue1) > POT_THRESHOLD) {
    controlChange(MIDI_CHANNEL, POT_CC_1, ccValue1);
    Serial.print("Pot 1 Value: ");
    Serial.println(ccValue1);
    lastPotValue1 = potValue1;
  }

  // Potentiometer 2
  int potValue2 = analogRead(POT_2);
  byte ccValue2 = map(potValue2, 0, 1023, 0, 127);
  if (abs(potValue2 - lastPotValue2) > POT_THRESHOLD) {
    controlChange(MIDI_CHANNEL, POT_CC_2, ccValue2);
    Serial.print("Pot 2 Value: ");
    Serial.println(ccValue2);
    lastPotValue2 = potValue2;
  }

}

