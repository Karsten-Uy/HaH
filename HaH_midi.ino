#include "MIDIUSB.h"
#include <Control_Surface.h>
#include "HaH_midi.h"

/*******************/
// GLOBAL VARIABLES
/*******************/

Mode currMode;

// States
bool buttonStates[6];
bool LEDStates[6];

bool delayState;
bool modeState;

int lastPotValue = -1; // Initialize to a value that won't match the initial read

// Define Control Change values for each button
const byte ccValues[6] = {16,17,18,19,20,21};

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
  pinMode(LED_2, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_0, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_M, OUTPUT);

  pinMode(BUT_2, INPUT_PULLUP);
  pinMode(BUT_1, INPUT_PULLUP);
  pinMode(BUT_0, INPUT_PULLUP);
  pinMode(BUT_5, INPUT_PULLUP);
  pinMode(BUT_4, INPUT_PULLUP);
  pinMode(BUT_3, INPUT_PULLUP);
  pinMode(BUT_M, INPUT_PULLUP);

  pinMode(BUT_D, INPUT_PULLUP);
  pinMode(LED_D, OUTPUT);
  pinMode(POT_EX, INPUT);

  for (int i = 0; i < 6; i++) {
    buttonStates[i] = false;  // Set each button state to false
    LEDStates[i] = false;
  }

  modeState = false;
  delayState = false;

  currMode = FX;
}

void loop() {
  bool currentState;

  /************************/
  // MODE SELECTOR
  /************************/

  currentState = digitalRead(BUT_M);
  if (currentState != modeState) {
    delay(DEBOUNCETIME); // Debounce delay

    if (currentState != modeState) {
      if (currentState == LOW) {
        currMode = static_cast<Mode>((currMode + 1) % 2); // Cycle through modes
        Serial.print("Current Mode: MODE_");
        Serial.println(static_cast<int>(currMode)); // Print the current mode number
      }
      modeState = currentState; // Update the mode state
    }
  }

  switch (currMode) {
  case FX:
    digitalWrite(LED_M, HIGH);
    break;
  case CH:
    digitalWrite(LED_M, LOW);
    break;
  default: // shouldn't happen but is here anyways
    break;
  }

  /************************/
  // CONTROL BUTTONS FX
  /************************/

  for (int i = 0; i < NUM_BUTTONS; i++) {
    currentState = digitalRead(buttonPins[i]);

    if (currentState != buttonStates[i]) {
      delay(DEBOUNCETIME); // Debounce delay

      if (currentState != buttonStates[i]) {
        if (currentState == LOW) {
          // Toggle LED, allows for TFF behavior
          LEDStates[i] = !LEDStates[i];

          // Send Control Change message
          controlChange(0, ccValues[i], LEDStates[i] ? 0 : 127); // Turn on/off based on LED state

          // Output the pressed button number to the serial monitor
          Serial.print("Button ");
          Serial.print(i);
          Serial.println(" pressed.");
        }

        buttonStates[i] = currentState; 
      }
    }

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

        controlChange(0, CC_MIDI_MODULATION, 127);
        digitalWrite(LED_D, HIGH);  // Turn on the corresponding LED

        delay(DELAY_TAP_LED_TIME);
        
        digitalWrite(LED_D, LOW);  // Turn off the corresponding LED
        controlChange(0, CC_MIDI_MODULATION, 0);

      } 
      delayState = currentState; // Update the mode state
    }
  }

  /************************/
  // POTENTIOMETER READ
  /************************/

  int potValue = analogRead(POT_EX); // Read the potentiometer value
  byte ccValue = map(potValue, 0, 1023, 0, 127); // Map to MIDI CC range

  // Check if the potentiometer value has changed
  if (abs(potValue - lastPotValue) > POT_THRESHOLD) {
    controlChange(0, CC_EFFECT_CONTROL_1, ccValue); // Send the Control Change message

    // Print the potentiometer value and mapped CC value
    Serial.print("Potentiometer Value: ");
    Serial.print(potValue);
    Serial.print(", Mapped CC Value: ");
    Serial.println(ccValue);

    // Update the last potentiometer value
    lastPotValue = potValue; 
  }

}
