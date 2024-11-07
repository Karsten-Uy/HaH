# 3 - Channel Mode
This mode routes the signal through specific channels for processing. The MIDI signals triggered by the select buttons are mapped to each channel's mute control, allowing only one channel to stay active at a time. The expression pedal remains mapped to global volume. When switching channels using the select buttons, the board sends a MIDI low signal to unmute the selected channel and a MIDI high signal to mute the remaining channels.

Refer to the `ccValues_CH` array in the `HaH_midi.h` file for midi CC assignments that map to the mute button of the channel.

### Pre Mode Select
Before entering this mode, the board sends MIDI control high signals to mute all channels except channel 0.

### On Switch
When switching modes from Channel, the board sends a MIDI control high signal to mute all seven channels in this mode.


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