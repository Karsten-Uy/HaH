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


// Array of LED pin constants
const int ledPins[7] = {LED_0, LED_1, LED_2, LED_3, LED_4, LED_5, LED_6};


// MIDI CC Assignments
const byte POT_CC_EX = 0;
const byte POT_CC_0 = 1;
const byte POT_CC_1 = 2;
const byte POT_CC_2 = 3;

const byte ccValues[6] = {16,17,18,19,20,21};




// MIDI Control Change Constants
const byte CC_BANK_SELECT = 0;                // Bank Select
const byte CC_MODULATION = 1;                  // Modulation Wheel
const byte CC_BREATH_CONTROL = 2;              // Breath Controller
const byte CC_FOOT_CONTROLLER = 4;             // Foot Controller
const byte CC_PORTAMENTO_TIME = 5;             // Portamento Time
const byte CC_DATA_ENTRY = 6;                   // Data Entry
const byte CC_CHANNEL_VOLUME = 7;               // Channel Volume
const byte CC_balance = 8;                      // Balance
const byte CC_PAN = 10;                         // Pan
const byte CC_EXPRESSION = 11;                  // Expression Controller
const byte CC_EFFECT_CONTROL_1 = 12;            // Effect Control 1
const byte CC_EFFECT_CONTROL_2 = 13;            // Effect Control 2
const byte CC_CHANNEL_PRESSURE = 13;            // Channel Pressure (Aftertouch)
const byte CC_PITCH_BEND = 14;                  // Pitch Bend Range
const byte CC_FX1_DEPTH = 91;                   // FX1 Depth
const byte CC_FX2_DEPTH = 92;                   // FX2 Depth
const byte CC_FX3_DEPTH = 93;                   // FX3 Depth
const byte CC_FX4_DEPTH = 94;                   // FX4 Depth
const byte CC_FX5_DEPTH = 95;                   // FX5 Depth
const byte CC_ALL_SOUND_OFF = 120;              // All Sound Off
const byte CC_RESET_ALL_CONTROLLERS = 121;     // Reset All Controllers
const byte CC_LOCAL_CONTROL = 122;              // Local Control
const byte CC_ALL_NOTES_OFF = 123;              // All Notes Off
const byte CC_OMNI_MODE_OFF = 124;              // Omni Mode Off
const byte CC_OMNI_MODE_ON = 125;               // Omni Mode On
const byte CC_MONO_MODE_ON = 126;               // Mono Mode On
const byte CC_POLY_MODE_ON = 127;               // Poly Mode On   //max is 127

// Additional commonly used MIDI CCs
const byte CC_SUSTAIN_PEDAL = 64;               // Sustain Pedal
const byte CC_SOFT_PEDAL = 67;                  // Soft Pedal
const byte CC_LEGATO_PEDAL = 68;                // Legato Pedal
const byte CC_HOLD_PEDAL = 69;                  // Hold Pedal
const byte CC_SOUND_VARIATION = 70;             // Sound Variation
const byte CC_SOUND_TIMBRE = 71;                // Sound Timbre
const byte CC_SOUND_RELEASE_TIME = 72;          // Sound Release Time
const byte CC_SOUND_ATTACK_TIME = 73;           // Sound Attack Time
const byte CC_SOUND_FILTER_CUTOFF_FREQUENCY = 74; // Sound Filter Cutoff Frequency
const byte CC_SOUND_FILTER_RESONANCE = 75;     // Sound Filter Resonance
const byte CC_SOUND_TUNE = 76;                  // Sound Tune
const byte CC_SOUND_LEVEL = 77;                 // Sound Level
const byte CC_MIDI_MODULATION = 78;             // MIDI Modulation

// Add additional custom CC constants as needed
