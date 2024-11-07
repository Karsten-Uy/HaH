# 1 - Kirbeats Mode
This mode is tailored to my (Karsten Kirby Uy) playing style, featuring five regular selectable channels and an expression pedal mapped to control global volume. It functions similarly to channel mode but includes two channels with distinct expression pedal mappings. Additionally, two selectable channels modify the MIDI signal sent by the expression pedal while keeping the volume at maximum. When switching channels using the select buttons, the board sends a MIDI low signal to unmute the selected channel and a MIDI high signal to mute the others.

Refer to the `ccValues_KB` array in the `HaH_midi.h` file for midi CC assignments that map to the mute button of the channel.

### Pre Mode Select
Before entering this mode, the board sends MIDI control high signals to mute all channels except channel 0, with the expression pedal mapped to global volume.

### On Switch
When switching modes from Kirbeats, the board maps the expression pedal to control global volume and sends a MIDI control high signal to mute all seven channels in this mode.


## Select Button Mappings

| Select Button Number | Expression Pedal Mapping | Functionality |
| -------------------- | ------------------------ | ------------- |
| 0                    | Gloabl Volume            | Bypass/Pass |
| 1                    | Gloabl Volume            | Bypass/Pass |
| 2                    | Gloabl Volume            | Bypass/Pass |
| 3                    | Gloabl Volume            | Bypass/Pass |
| 4                    | Gloabl Volume            | Bypass/Pass |
| 5                    | Custom                   | Bypass/Pass with global volume set to maximum, and the expression pedal switched to control the CC channel specified by `POT_CC_KB_5` |
| 6                    | Custom                   | Bypass/Pass with global volume set to maximum, and the expression pedal switched to control the CC channel specified by `POT_CC_KB_6` |