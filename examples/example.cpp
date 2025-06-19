#include <Adafruit_NeoPixel.h>
#include "LEDAnimation.h"

#define LED_PIN 5
#define NUM_LEDS 16

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
LEDAnimation animation(strip, NUM_LEDS);

void setup() {
  strip.begin();
  strip.show();

  animation.setColor(strip.Color(0, 255, 0));
  animation.setDelaySpeed(5);
  animation.setAnimation(AnimationType::StartUp);
}

void loop() {
  // nichts notwendig, alles läuft im Hintergrund-Task
}