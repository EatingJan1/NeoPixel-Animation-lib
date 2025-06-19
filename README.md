# NeoPixel-Animation-lib - Arduino Library for LED Animations

This library provides an easy-to-use interface for controlling NeoPixel-based LED strips on ESP32 using predefined animations. It uses FreeRTOS tasks to run animations in the background, letting your main code stay clean and responsive.

---

## Introduction

With the `NeoPixel-Animation-lib`, you can add beautiful visual alerts or status indicators to your projects without writing complex animation logic yourself.

This library allows you to:

* Set different **predefined animation modes**
* Adjust animation **speed** and **color**
* Let animations run **independently in the background**

Compatible with:

* **ESP32**
* **Adafruit NeoPixel LED strips**

---

## Installation

### Using PlatformIO:

```ini
lib_deps =
  adafruit/Adafruit NeoPixel
  https://github.com/EatingJan1/NeoPixel-Animation-lib.git
```

### Using Arduino IDE:

1. Download the ZIP of this repository
2. Unzip and place in your `Arduino/libraries/` folder
3. Install the "Adafruit NeoPixel" library via Library Manager

---

## Supported Animations

You can choose one of the following predefined animations by calling:

```cpp
animation.setAnimation(AnimationType::AnimationName);
```

| AnimationType     | Description                                                                |
| ----------------- | -------------------------------------------------------------------------- |
| `None`            | Turns off all LEDs                                                         |
| `CriticalWarning` | Blinking red alert pattern                                                 |
| `StartUp`         | Sequential LED lighting like a boot-up indicator                           |
| `Rotating`        | A moving LED with a trailing effect                                        |
| `Connection`      | Fade-in and fade-out pattern, ideal for WiFi/Bluetooth connection feedback |
| `Static`          | All LEDs set to a solid color                                              |

---

## Public Methods

### Set Animation

```cpp
bool setAnimation(AnimationType type);
```

Sets the animation mode. Returns `false` if already active.

### Set Color

```cpp
void setColor(uint32_t color);
```

Changes the color of the animation.

Example:

```cpp
animation.setColor(strip.Color(255, 0, 0)); // red
```

### Set Speed

```cpp
void setDelaySpeed(uint delay);
```

Controls how fast the animation runs (lower = faster).

