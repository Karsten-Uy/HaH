# 2 - FX Mode
FX Mode is designed to stack effects on a single channel, with the MIDI value select button mapped to bypass specific effects on that channel in the DAW. A MIDI CC signal mutes or unmutes the channel when switching modes, while the expression pedal remains mapped to global volume.

Refer to the `ccValues_CH` array in the `HaH_midi.h` file for MIDI CC assignments mapped to each effect bypass button, and to `CC_FX_MUTE` for the MIDI CC value that controls channel muting.

### Pre Mode Select
Before entering FX Mode, the board sends MIDI high signals to bypass all effects channels and a MIDI low signal to unmute the FX channel.

### On Switch
When switching out of FX Mode, the board sends MIDI high signals to bypass all effects channels and a MIDI high signal to mute the FX channel.


## Select Button Mappings

| Select Button Number | Expression Pedal Mapping | Functionality |
| -------------------- | ------------------------ | ------------- |
| 0                    | Gloabl Volume            | Bypass/Pass |
| 1                    | Gloabl Volume            | Bypass/Pass |
| 2                    | Gloabl Volume            | Bypass/Pass |
| 3                    | Gloabl Volume            | Bypass/Pass |
| 4                    | Gloabl Volume            | Bypass/Pass |
| 5                    | Gloabl Volume            | Bypass/Pass |
| 6                    | Gloabl Volume            | Bypass/Pass |