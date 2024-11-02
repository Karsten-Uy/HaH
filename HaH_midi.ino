#include "MIDIUSB.h"
#include <Control_Surface.h>

// Input Pins

const int B1IN = 10;

// Button States

bool B1STATE;

// other

const int BCHANNEL = 0;
const int DEBOUNCETIME = 10;
const int RELEASEVEL = 127;

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

// Actual stuff

void setup() {

  Serial.begin(9600);

  pinMode(B1IN,INPUT_PULLUP);

  B1STATE = LOW;

}

void loop() {

  // Non Hats

  if (digitalRead(B1IN) != B1STATE) {

    delay(DEBOUNCETIME);

    if (digitalRead(B1IN) != B1STATE) {

      B1STATE = !B1STATE;

      if (B1STATE != LOW) {
        noteOn(BCHANNEL, MIDI_Notes::C[2], 0);
      } else {
        noteOn(BCHANNEL, MIDI_Notes::C[2], RELEASEVEL);
      }

      MidiUSB.flush();

    }

  }

}