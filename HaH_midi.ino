#include "MIDIUSB.h"
#include "HaH_midi.h"

/*******************/
// GLOBAL VARIABLES
/*******************/

Mode currMode;

// States
bool LEDStates[7];

bool delayState;
unsigned long pressStartTime = 0;
bool holding;
bool holdSignalSent;
bool isMute;
bool unmuteReady;

bool modeState; // Flag to track if button press was detected

bool isKB_5;
bool isKB_6;

int lastPotValueEx = -1;
int lastPotValue0 = -1;
int lastPotValue1 = -1;
int lastPotValue2 = -1;
bool lastButRead[3] = {0, 0, 0};

bool butRead[3];

// Timer variables for LED flashing
unsigned long lastFlashTime = 0;      // Tracks last flash timestamp
unsigned long lastSequenceTime = 0;   // Tracks time between sequences
int flashCount = 0;                   // Counts flashes in a sequence
bool ledState = LOW;                  // Tracks current LED state (on or off)

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
    controlChange(MIDI_CHANNEL, ccValues_FX[i], 127);
    controlChange(MIDI_CHANNEL, ccValues_CH[i], 127);
  }

  for (int i = 0; i < sizeof(butRead) / sizeof(butRead); i++) {
    butRead[i] = false;
  }

  delayState = false;
  holding = false;
  holdSignalSent = false;
  isMute = false;
  unmuteReady = false;

  modeState = false;

  // Set default mode to Kirbeats Mode
  currMode = KB;
  LEDStates[0] = true; // Let 1 channel through
  controlChange(MIDI_CHANNEL, ccValues_KB[0], 0);
  isKB_5 = false;
  isKB_6 = false;

}

void loop() {

  bool currentState;

  /************************/
  // MODE SELECTOR
  /************************/

  // Read button state
  currentState = digitalRead(BUT_M);

  // Check for button press and release
  if (currentState == LOW && !modeState) { // Button is pressed (assuming LOW is pressed)
      delay(DEBOUNCETIME); // Debounce delay

      if (digitalRead(BUT_M) == LOW) { // Confirm the button is still pressed after debounce
          modeState = true; // Set flag to indicate button is currently pressed

          //------------------------------
          // RESETS - Pre Switch

          switch (currMode) { // This runs before any processing for that mode

          case KB:
              for (int i = 0; i < sizeof(LEDStates) / sizeof(LEDStates[0]); i++) {
                  controlChange(MIDI_CHANNEL, ccValues_KB[i], 127);
              }
              break;

          case FX:
              for (int i = 0; i < sizeof(LEDStates) / sizeof(LEDStates[0]); i++) {
                  controlChange(MIDI_CHANNEL, ccValues_FX[i], 127);
              }
              controlChange(MIDI_CHANNEL, CC_FX_MUTE, 127);
              break;

          case CH:
              for (int i = 0; i < sizeof(LEDStates) / sizeof(LEDStates[0]); i++) {
                  controlChange(MIDI_CHANNEL, ccValues_CH[i], 127);
              }
              break;

          default:
              break;
          }

          // Change mode
          currMode = static_cast<Mode>((currMode + 1) % 3); // Cycle through modes
          Serial.print("Current Mode: ");
          Serial.println(currMode); // Print the current mode number

          //---------------------------
          // RESETS - Post Switch

          switch (currMode) { // This runs after switching modes

          case KB:
              for (int i = 0; i < sizeof(LEDStates) / sizeof(LEDStates[0]); i++) {
                  LEDStates[i] = false;
              }
              LEDStates[0] = true; // Let 1 channel through
              controlChange(MIDI_CHANNEL, ccValues_KB[0], 0);
              break;

          case FX:
              for (int i = 0; i < sizeof(LEDStates) / sizeof(LEDStates[0]); i++) {
                  LEDStates[i] = false;
              }
              controlChange(MIDI_CHANNEL, CC_FX_MUTE, 0);
              break;

          case CH:
              for (int i = 0; i < sizeof(LEDStates) / sizeof(LEDStates[0]); i++) {
                  LEDStates[i] = false;
              }
              LEDStates[0] = true; // Let 1 channel through
              controlChange(MIDI_CHANNEL, ccValues_CH[0], 0);
              break;

          default:
              break;
          }

          flashCount = 0; // Reset flash count
          lastSequenceTime = millis(); // Start the wait timer for the sequence
      }

  } else if (currentState == HIGH && modeState) {
      // Button released
      modeState = false; // Reset flag for next press
  }

  /************************/
  // FLASHING
  /************************/

  unsigned long currentTime = millis();

  if (flashCount < static_cast<int>(currMode) + 1) {
    // Check if it's time to toggle the LED state for a flash
    if (currentTime - lastFlashTime >= MODE_LIGHT_FLASH_TIME) {
      ledState = !ledState;  // Toggle LED state
      digitalWrite(LED_M, ledState); // Set LED based on ledState
      lastFlashTime = currentTime;

      // If the LED just turned off, increment the flash count
      if (ledState == LOW) {
          flashCount++;
      }
    }
  } else {
    // Wait for the interval before starting the next sequence
    if (currentTime - lastSequenceTime >= MODE_LIGHT_WAIT_TIME) {
      flashCount = 0; // Reset flash count for the next sequence
      lastSequenceTime = currentTime; // Reset sequence timer
    }
  }
    
  
  //--------------------------------------
  // CONTROL BUTTONS FX

  butRead[0] = digitalRead(BUT_BIN_0);
  butRead[1] = digitalRead(BUT_BIN_1);
  butRead[2] = digitalRead(BUT_BIN_2);

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

      //---------------------------
      // KIRBEATS MODE SELECT BUTTONS 

      case KB:

        for (int i = 0; i < sizeof(LEDStates) / sizeof(LEDStates[0]); i++) {

          if (i == numBut) {
            controlChange(MIDI_CHANNEL, ccValues_KB[i], 0);
            LEDStates[i] = true;
          } else {
            controlChange(MIDI_CHANNEL, ccValues_KB[i], 127);
            LEDStates[i] = false;
          }

          // Bypass expression pedal to map the pedal to something else
          if (numBut == 5) { 
            controlChange(MIDI_CHANNEL, POT_CC_EX, 127);
            isKB_5 = true;
          } 

          if (numBut == 6) {
            controlChange(MIDI_CHANNEL, POT_CC_EX, 127);
            isKB_6 = true;
          }

        }

        if (numBut != 5) {
          isKB_5 = false;
        }
        if (numBut != 6) {
          isKB_6 = false;
        }

        break;

      //---------------------------
      // FX MODE SELECT BUTTONS 

      case FX:

        // Toggle the LED state for the button
        LEDStates[numBut] = !LEDStates[numBut];

        controlChange(MIDI_CHANNEL, ccValues_FX[numBut], LEDStates[numBut] ? 0 : 127);

        break;

      //---------------------------
      // CHANNEL MODE SELECT BUTTONS 

      case CH:

        for (int i = 0; i < sizeof(LEDStates) / sizeof(LEDStates[0]); i++) {

          if (i == numBut) {
            controlChange(MIDI_CHANNEL, ccValues_CH[i], 0);
            LEDStates[i] = true;
          } else {
            controlChange(MIDI_CHANNEL, ccValues_CH[i], 127);
            LEDStates[i] = false;
          }

        }

        break;

      default: // shouldn't happen but is here anyways
        break;
      }
     
      // Output the button number to the serial monitor
      Serial.print("Select Button ");
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
  // DELAY TAPPER / MUTE
  /************************/

  currentState = digitalRead(BUT_D);
  if (currentState != delayState) {
      delay(DEBOUNCETIME); // Debounce delay

      if (currentState != delayState) {
          if (currentState == LOW) {  // Button pressed

              // If already muted, prepare for unmute on tap release
              if (isMute && !holding) {
                  unmuteReady = true;  // Set flag to allow unmute on release
              }

              Serial.println("Delay Tapped");
              controlChange(MIDI_CHANNEL, DEL_TAP_CC, 127);
              delay(DELAY_TAP_LED_TIME);
              controlChange(MIDI_CHANNEL, DEL_TAP_CC, 0);

              // Start holding logic for the current press
              pressStartTime = millis();
              holding = true;
              holdSignalSent = false; // Reset hold signal for this press

          } else {  // Button released

              if (unmuteReady) {  // Check if ready to unmute on release

                  controlChange(MIDI_CHANNEL, MUTE_CC, 0);
                  Serial.println("Unmuted");
                  digitalWrite(LED_D, LOW);  // Turn off the corresponding LED
                  isMute = false;
                  unmuteReady = false;  // Reset unmute flag

              }

              holding = false; // Reset holding status on release
          }

          delayState = currentState; // Update the mode state
      }
  }

  // Holding check, independent of the initial button press check
  if (!unmuteReady && holding && !holdSignalSent && (millis() - pressStartTime >= MUTE_HOLD_TIME)) {
      
      // Trigger mute action for holding
      controlChange(MIDI_CHANNEL, MUTE_CC, 127);
      Serial.println("Mute triggered!");
      digitalWrite(LED_D, HIGH);  // Turn on the corresponding LED
      isMute = true;

      holdSignalSent = true; // Ensure hold signal is only sent once per press
      unmuteReady = false;   // Reset unmute readiness since it's now held

  }


  /************************/
  // POTENTIOMETER READS
  /************************/

  // Read each potentiometer and send MIDI CC if the value has changed

  // Potentiometer EX
  int potValueEx = analogRead(POT_EX);
  byte ccValueEx = map(potValueEx, POT_EX_START_VAL, POT_EX_END_VAL, 0, 127);

  if (abs(potValueEx - lastPotValueEx) > POT_THRESHOLD) { 

    byte potExCC;

    if (isKB_5) {
      potExCC = POT_CC_KB_5;
    } else if (isKB_6) {
      potExCC = POT_CC_KB_6;
    } else {
      potExCC = POT_CC_EX;
    }

    controlChange(MIDI_CHANNEL, potExCC, ccValueEx);

    Serial.print("Pot EX Value: ");
    Serial.println(ccValueEx);
    lastPotValueEx = potValueEx;
  }

  // Potentiometer 0
  int potValue0 = analogRead(POT_0);
  byte ccValue0 = map(potValue0, 0, 1023, 0, 127);
  if (abs(potValue0 - lastPotValue0) > POT_THRESHOLD) {
    controlChange(MIDI_CHANNEL, POT_CC_0, 127 - ccValue0);
    Serial.print("Pot 0 Value: ");
    Serial.println(ccValue0);
    lastPotValue0 = potValue0;
  }

  // Potentiometer 1
  int potValue1 = analogRead(POT_1);
  byte ccValue1 = 127 - map(potValue1, 0, 1023, 0, 127);
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
    controlChange(MIDI_CHANNEL, POT_CC_2, 127 - ccValue2);
    Serial.print("Pot 2 Value: ");
    Serial.println(ccValue2);
    lastPotValue2 = potValue2;
  }

}

