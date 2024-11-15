# Helix at Home (HaH)

This project is an Arduino-based MIDI controller, designed with an Arduino Pro Micro to manage buttons, potentiometers, and LEDs for controlling MIDI effects and channel settings, effectively simulating a guitar pedalboard. The controller features multiple modes that alter the behavior of MIDI controls, allowing for versatile customization of effects. 

- For setup and usage details, refer to the "Usage Documentation" folder.
- For details on MIDI outputs, refer to the "MIDI CC Assignments" sections in the "HaH_midi.h" file

![BOARD IMAGE](/Images/HaH_main.jpg)

## Documentation Table of Contents
- [General Usage](https://github.com/Karsten-Uy/HaH/blob/main/Usage%20Documentation/General%20Usage.md)
- [Arduino and Electrical Setup](https://github.com/Karsten-Uy/HaH/blob/main/Usage%20Documentation/Arduino%20and%20Electrical%20Setup.md)
- Modes
    1. [Kirbeats](https://github.com/Karsten-Uy/HaH/blob/main/Usage%20Documentation/Modes/1-Kirbeats.md)
    2. [FX](https://github.com/Karsten-Uy/HaH/blob/main/Usage%20Documentation/Modes/2-FX.md)
    3. [Channel](https://github.com/Karsten-Uy/HaH/blob/main/Usage%20Documentation/Modes/3-Channel.md)

## Features
For more detailed functionality see the "Usage Documentation" folder.
- **Multi Mode Control**: Switch between Channel (CH) and Effects (FX) modes.
- **MIDI Control Change (CC) Messages**: Has has following buttons and potentiometers that send specific MIDI CC messages for flexible control.
    - 7 Select Buttons
    - 1 Mode Select Buttons
    - 1 Mute / Delay Tapper Button
    - 3 Global Potentiometers
    - 1 Expression Pedal

- **Debouncing**: Smooth button presses to reduce unintended triggers.
- **Potentiometer Calibration**: Adjustable sensitivity and threshold for accurate readings.
- **Visual Feedback**: LEDs provide visual status of each mode and button press.

## Components
- **Arduino Pro Micro** - The microcontroller board.
- **Select Buttons (Digital)** - Used for switching modes, effects, and channels.
- **LEDs** - Provide visual feedback.
- **Potentiometers (Analog)** - Used to adjust effect levels.
- **MIDIUSB** - Libraries for MIDI communication.
- **Physical Board** - Built with the following to structure and hold the eletrical components
    - Paper Organizer for base
    - Tape
    - Macbook Box for structure and button covers
    - Lego for pedal 
    - Trampoline Park Sock fir grip on pedal
## Configuration
- **Debounce Time (`DEBOUNCETIME`)**: Adjusts the debounce delay in milliseconds.
- **Potentiometer Calibration (`POT_EX_START_VAL`, `POT_EX_END_VAL`)**: Defines the sensitivity range for the main potentiometer.
- **MIDI Channel**: Configured via `MIDI_CHANNEL`, which can be changed based on your MIDI setup.



