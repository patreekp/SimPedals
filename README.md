# DIY Pedal Set for Sim Racing – Arduino USB Joystick

This project turns a set of **DIY pedals** — throttle with a standard potentiometer, brake and clutch using **hydraulic pressure sensors / analog pressure transducers** — into a fully functional **USB game controller** for racing simulators.

An Arduino board reads the sensors, optionally performs **dynamic auto-calibration**, maps the values, and exposes them to the PC via the **Joystick.h** HID library.

---

## ✨ Features

* **Reads 3 pedal inputs**:

  * Throttle (potentiometer)
  * Brake (pressure transducer)
  * Clutch (pressure transducer)
* **Native USB HID joystick** (no drivers required)
* **Optional dynamic auto-calibration**
* **Automatic mapping to the full 0–1023 range**
* **Low-latency update loop (10 ms)**

---

## 🧰 Required Hardware

* **Arduino Leonardo / Micro / Pro Micro**
  (required because they support native USB HID)
* Sensors:

  * Linear or rotary potentiometer (throttle)
  * 0–5V analog pressure sensors (brake & clutch)
* Basic wiring to the analog inputs

---

## 🗂️ Pinout

| Pedal    | Arduino Pin |
| -------- | ----------- |
| Throttle | A0          |
| Brake    | A2          |
| Clutch   | A1          |

These pins can be changed in the configuration section of the code.

---

## 🔧 Software Configuration

Two important configuration flags are available:

### Auto-calibration

```cpp
#define ENABLE_AUTOCALIBRATION true
```

* Tracks the minimum and maximum values dynamically
* Makes the pedal set self-adapting to sensor tolerances

### Value mapping

```cpp
#define ENABLE_MAPPING true
```

* Maps real sensor range → 0..1023
* Recommended for smoother and more uniform pedal output

---

## 📦 Required Library

Install the **Joystick** library by Matthew Heironimus:

**Arduino IDE → Tools → Manage Libraries → search “Joystick” → Install**

---

## 🧩 Full Source Code

```cpp
<place your code here>
```

---

## 🚀 Usage

1. Upload the sketch to your Arduino board.
2. Connect all sensors to the analog pins as listed above.
3. The device will appear in your OS as a **USB Joystick**.
4. Test the pedal movement using “Game Controllers” (Windows) or any calibration tool.
5. Assign pedal inputs inside your racing simulator (Assetto Corsa, iRacing, ETS2, etc.).

---

## 📌 Notes

* With **auto-calibration enabled**, the first few pedal presses help the Arduino learn the min/max sensor range.
* If your sensors have a fixed or narrow range, you may disable auto-calibration and manually set the raw min/max values in the code.

