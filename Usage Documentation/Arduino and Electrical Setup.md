# Arduino and Electrical Setup

This age has the details on how the arduino and the circuits are set up

## Pin Assignments

The following table shows the pin assignments needed for this code to work.

| Pin Number | Description                           | Assignment |
|------------|---------------------------------------| -----------|
| RAW        | Unregulated voltage input (up to 12V) |
| VCC        | Regulated 5V output                   |
| GND        | Ground                                |
| RST        | Reset                                 |
| TX0        | Serial Transmit (TX) - Digital Pin 1  | BUT_BIN_0  |
| RX1        | Serial Receive (RX) - Digital Pin 0   | BUT_BIN_1  |
| 2          | Digital Pin 2                         | BUT_BIN_2  |
| 3          | Digital Pin 3 / PWM                   | LED_D      |
| 4          | Digital Pin 4                         | BUT_D      |
| 5          | Digital Pin 5 / PWM                   | LED_2      |
| 6          | Digital Pin 6 / PWM                   | LED_1      |
| 7          | Digital Pin 7                         | LED_0      |
| 8          | Digital Pin 8                         | LED_3      |
| 9          | Digital Pin 9 / PWM                   | LED_6      |
| 10         | Digital Pin 10 / PWM                  | LED_4      |
| 14         | Digital Pin 14                        | LED_M      |
| 15         | Digital Pin 15                        | BUT_M      |
| 16         | Digital Pin 16                        | LED_5      |
| A0         | Analog Pin 0                          | POT_2      |
| A1         | Analog Pin 1                          | POT_1      |
| A2         | Analog Pin 2                          | POT_0      |
| A3         | Analog Pin 3                          | POT_EX     |

## Wiring

### LEDs

For each LED, connect it in series with a resistor, and then connect the other end of the resistor to one of the board’s ground pins. Make sure the LED is oriented in forward bias (positive side to the signal, negative side to ground) to allow current to flow properly.

### Potentiometers

Connect the two outer pins to ground (GND) and power (VCC), and connect the middle pin to the corresponding analog input pin on the board. If turning the potentiometer changes the signal in the opposite direction of what you expect, swap the GND and VCC connections.

### BUT_M & BUT_D

Conenct the buttons to the correspong pin and then to ground, such that when the circuit completes, the input is grounded.

### BUT_BIN

Build the circuit to convert a "1-hot" signal into binary encoding. Each button is linked to a specific input, generating a unique binary value that the Arduino can interpret. When a button is pressed, the Arduino detects the rising edge of the corresponding signal, allowing it to identify which button was activated. If no button is pressed, the Arduino reads a "0" (no-signal) state.

[INSERT CIRCUIT IMAGE HERE]