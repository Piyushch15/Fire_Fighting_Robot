# FireFightingRobot 

An **autonomous fire-fighting robot** built using Arduino, 3 flame sensors, a water pump (relay controlled), and a sweeping servo for targeted spraying.

## Features
- Detects fire direction using **3 analog flame sensors**.
- Automatically approaches fire and **activates water pump**.
- Sweeps servo to cover fire area.
- Uses **L298N motor driver** for motion.
- **Easy calibration** using `FIRE_THRESHOLD`.

## Pin Configuration
| Component            | Pin |
|----------------------|-----|
| Flame Sensor Left    | A1  |
| Flame Sensor Center  | A2  |
| Flame Sensor Right   | A3  |
| Motor Driver L1      | D5  |
| Motor Driver L2      | D6  |
| Motor Driver R1      | D9  |
| Motor Driver R2      | D10 |
| Relay (Pump)         | D7  |
| Servo Signal         | D3  |
| Debug LED (optional) | D13 |

## How to Use
1. Open `FireFightingRobot.ino` in Arduino IDE.
2. Install the Servo library (built-in).
3. Upload the code to Arduino.
4. Adjust `FIRE_THRESHOLD` for proper calibration.

## Safety Notes
- Keep electronics and water pump isolated properly.
- Use separate power supply for motors/pump with common GND.

## License
Licensed under the [MIT License](LICENSE).

**Author:** [Piyush Channote](https://github.com/Piyushch15)
