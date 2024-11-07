# General Usage

The board operates with multiple modes that alter the MIDI signals sent by the select buttons, expression pedal, and other controls. It includes three potentiometers, which are recommended for mapping to global controls, as well as a tap tempo and mute button for flexible audio management. For specific details on MIDI CC assignments, refer to the `MIDI CC Assignments` section in the  `HaH_midi.h` file.

## Tap / Mute
The Tap Mute button, located at the bottom right of the board, serves two primary functions: tap tempo and mute control.

![Mute Image](/Images/mute.jpg)

### Tap Tempo
When the button is tapped repeatedly, it generates short MIDI control signal pulses that the device interprets as taps. These taps can be mapped to the tap delay macro in a digital audio workstation (DAW), allowing for real-time tempo adjustments.

### Mute Functionality
If the button is held down for the duration specified in the MUTE_HOLD_TIME variable in the "HaH_midi.h" file, it sends a MIDI "on" signal. This signal can be mapped to mute the audio output. When the button is released after a second tap, it sends a MIDI "off" signal, which can be mapped to unmute the audio if configured correctly. If the light below the "MUTE" label is on, then it is muted.


## Expression Pedal
Located at the top right of the board, the expression pedal controls a single MIDI signal, which is typically mapped to volume. This control can be toggled on or off depending on the current mode. Refer to the mode documentation for further details. The pedal sends MIDI values ranging from 0 to 127.

![Expression Pedal Image](/Images/expression.jpg)

## Gloabl Potentiometers
There are three global potentiometers at the top left of the board. These do not change with different modes and consistently send MIDI values from 0 to 127.

![Potentiometers Image](/Images/pot.jpg)

## Mode Select
The "MODE" button, located at the bottom right of the board, enables you to switch between modes. Pressing the button cycles through the modes, indicated by the light below the "MODE" label. The light flashes to show the current mode, with each mode identified by its respective number of flashes. These modes adjust the MIDI signals sent by the select buttons and, in some cases, the expression pedal. For detailed descriptions of each mode, refer to the documentation in the "Modes" folder. Available modes include:

1. [Kirbeats](https://github.com/Karsten-Uy/HaH/blob/main/Usage%20Documentation/Modes/1-Kirbeats.md)
2. [FX](https://github.com/Karsten-Uy/HaH/blob/main/Usage%20Documentation/Modes/2-FX.md)
3. [Channel](https://github.com/Karsten-Uy/HaH/blob/main/Usage%20Documentation/Modes/3-Channel.md)

#### Mode Button and Indicator
![Mode Image](/Images/mode.jpg)

#### Select Buttons and Indicators
![Mode Image](/Images/select.jpg)


