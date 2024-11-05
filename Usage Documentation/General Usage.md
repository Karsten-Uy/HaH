# General Usage

The board operates with multiple modes that alter the MIDI signals sent by the select buttons, expression pedal, and other controls. It includes three potentiometers, which are recommended for mapping to global controls, as well as a tap tempo and mute button for flexible audio management. For specific details on MIDI channel assignments, refer to the `MIDI CC Assignments` section in the  `HaH_midi.h` file.



## Tap / Mute
The Tap Mute button, located at the bottom right of the board, serves two primary functions: tap tempo and mute control.

### Tap Tempo
When the button is tapped repeatedly, it generates short MIDI control signal pulses that the device interprets as taps. These taps can be mapped to the tap delay macro in a digital audio workstation (DAW), allowing for real-time tempo adjustments.

### Mute Functionality
If the button is held down for the duration specified in the MUTE_HOLD_TIME variable in the "HaH_midi.h" file, it sends a MIDI "on" signal. This signal can be mapped to mute the audio output. When the button is released after a second tap, it sends a MIDI "off" signal, which can be mapped to unmute the audio if configured correctly.



## Expression Pedal
The expression pedal is the pedal on the top right of the board. By default it controls 1 midi signal which is recommended to be mapped to volume but it can be toggled on and off depending on which mode you are in. See the mode documentation for more details.


