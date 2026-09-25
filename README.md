# Non-Blocking Door Status Display (Arduino, millis)

A small Arduino program that shows visitor messages on a 16x2 I2C LCD, selected with three push buttons. It is written as a reference example of non-blocking timing with `millis()` instead of `delay()`: button handling stays responsive while a message is displayed and automatically cleared.

Typical use: a status panel outside an office door.

## Behaviour

| Button | Pin | Message displayed |
| --- | --- | --- |
| BP1 | D8 | `PATIENTEZ` / `Mr(Mme)` (please wait) |
| BP2 | D9 | `ENTREZ` / `Mr(Mme)` (come in) |
| BP3 | D10 | `JE SUIS` / `ABSENT` (I am away) |

Each message stays on screen for 20 seconds and is then cleared automatically. Every event is also logged on the serial port at 9600 baud.

## Techniques demonstrated

- Edge detection on inputs using `INPUT_PULLUP`
- Per-button debouncing without blocking the main loop
- A timed display state managed with `millis()` timestamps

## Hardware

- Arduino Uno or Nano
- 16x2 LCD with I2C backpack at address `0x27` (SDA on A4, SCL on A5 for Uno/Nano)
- 3 push buttons wired between the input pin and GND

## Build

1. Install the `LiquidCrystal_I2C` library.
2. Copy `lcd_boutons_millis_V2.cpp` into an Arduino sketch (rename it to `.ino`), or add it to a PlatformIO project under `src/`.
3. Upload to the board.

If the display stays blank, confirm the I2C address with an I2C scanner sketch (`0x3F` is also common).

## License

No license has been specified yet. Contact the author before reusing this code.
