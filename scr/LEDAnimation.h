#ifndef LEDANIMATION_H
#define LEDANIMATION_H

#include <Adafruit_NeoPixel.h>

enum class AnimationType {
    None,
    CriticalWarning,
    StartUp,
    Rotating,
    Connection,
    Static
};

class LEDAnimation {
public:
    LEDAnimation(Adafruit_NeoPixel Pin, int countofPins);
    ~LEDAnimation();
    
    bool setAnimation(AnimationType animationNumber);
    void setColor(uint32_t color);
    void setDelaySpeed(uint delay);
    void update();

private:


    void StopAllAnimations();
    void setAll(uint32_t color);
    
    void activateCritical();
    void activateStartup();
    void activateRotating();
    void activateConnection();
    void activateStatic();

    //void updateCritical(unsigned long currentMillis);
    //void updateStartup(unsigned long currentMillis);
    //void updateRotating(unsigned long currentMillis);
    //void updateConnection(unsigned long currentMillis);

    void updateCritical();
    void updateStartup();
    void updateRotating();
    void updateConnection();

    Adafruit_NeoPixel ledPin;
    int count;
    int despeed = 10;
    
    AnimationType activeAnimation;
    unsigned long lastUpdate;
    int currentStep;
    uint32_t animationColor;

    TaskHandle_t taskHandle;
    
    static void taskFunction(void* params);
    void run();
    
    static const uint16_t CRITICAL_BLINK_INTERVAL = 200;
    static const uint16_t STARTUP_LED_INTERVAL = 50;
    static const uint16_t ROTATING_INTERVAL = 100;
    static const uint16_t CONNECTION_INTERVAL = 100;
    static const uint16_t CONNECTION_FINAL_DELAY = 500;

    const uint32_t CRITICAL_COLOR = Adafruit_NeoPixel::Color(255, 0, 0);
    const uint32_t STARTUP_COLOR = Adafruit_NeoPixel::Color(0, 0, 255);
    const uint32_t FINAL_STARTUP_COLOR = Adafruit_NeoPixel::Color(0, 255, 0);
    const uint32_t ROTATING_COLOR = Adafruit_NeoPixel::Color(0, 255, 0);
    const uint32_t CONNECTION_COLOR = Adafruit_NeoPixel::Color(255, 0, 0); 
    const uint32_t STATIC_COLOR = Adafruit_NeoPixel::Color(0, 255, 0); 
    
    uint32_t color = Adafruit_NeoPixel::Color(255, 255, 255);
};

#endif