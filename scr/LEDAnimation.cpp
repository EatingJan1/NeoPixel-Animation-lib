#include "LEDAnimation.h"
#include <Arduino.h>

LEDAnimation::LEDAnimation(Adafruit_NeoPixel Pin, int countofPins)
    : ledPin(Pin),
      count(Pin.numPixels()),
      activeAnimation(AnimationType::None),
      lastUpdate(0),
      currentStep(0) 
{
    BaseType_t taskCreated = xTaskCreate(
        taskFunction,
        "LEDTask",
        2048,
        this,
        3,
        &taskHandle
    );
}


LEDAnimation::~LEDAnimation() {
    if(taskHandle != NULL) {
        vTaskDelete(taskHandle);
    }
}

void LEDAnimation::taskFunction(void* params) {
    LEDAnimation* instance = static_cast<LEDAnimation*>(params);
    while(true) {
        instance->update();
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

void LEDAnimation::setAnimation(AnimationType animationNumber) {
    StopAllAnimations();
    
    switch(animationNumber) {
        case AnimationType::CriticalWarning: activateCritical(); break;
        case AnimationType::StartUp: activateStartup(); break;
        case AnimationType::Rotating: activateRotating(); break;
        case AnimationType::Connection: activateConnection(); break;
        case AnimationType::Static: activateStatic(); break;
        default: StopAllAnimations(); break;
    }
    
}

void LEDAnimation::setColor(uint32_t color)
{
    this->color = color;
}

void LEDAnimation::setDelaySpeed(uint delay)
{
    this->despeed;
}

void LEDAnimation::StopAllAnimations() {
    activeAnimation = AnimationType::None;
    ledPin.clear();
    ledPin.show();
}

void LEDAnimation::setAll(uint32_t color) {

    ledPin.fill(color);
    ledPin.show();
}

void LEDAnimation::update() {
    uint32_t currentTime = xTaskGetTickCount() * portTICK_PERIOD_MS;
    
    switch(activeAnimation) {
        case AnimationType::CriticalWarning:
            updateCritical();
            break;
        case AnimationType::StartUp:
            updateStartup();
            break;
        case AnimationType::Rotating:
            updateRotating();
            break;
        case AnimationType::Connection:
            updateConnection();
            break;
        case AnimationType::Static:
            break;
        default:
            break;
    }
}


void LEDAnimation::activateCritical() {
    activeAnimation = AnimationType::CriticalWarning;
    currentStep = 0;
    lastUpdate = xTaskGetTickCount() * portTICK_PERIOD_MS;
    setAll(CRITICAL_COLOR);
}

void LEDAnimation::activateStartup() {
    activeAnimation = AnimationType::StartUp;
    currentStep = 0;
    lastUpdate = xTaskGetTickCount() * portTICK_PERIOD_MS;
    setAll(0);
}

void LEDAnimation::activateRotating() {
    activeAnimation = AnimationType::Rotating;
    currentStep = 0;
    lastUpdate = xTaskGetTickCount() * portTICK_PERIOD_MS;
    setAll(0);
    ledPin.setPixelColor(count, ROTATING_COLOR);
    ledPin.show();
}

void LEDAnimation::activateConnection() {
    activeAnimation = AnimationType::Connection;
    currentStep = 0;
    lastUpdate = xTaskGetTickCount() * portTICK_PERIOD_MS;
    setAll(0);
}
void LEDAnimation::activateStatic() {
    activeAnimation = AnimationType::Static;
    setAll(color);
}



void LEDAnimation::updateCritical() {
    uint32_t currentTime = xTaskGetTickCount() * portTICK_PERIOD_MS;

    for(int i = 0; i<=count; i++)
    {
        if ((i%2 == 0 and currentStep%2 == 1) or (i%2 == 1 and currentStep%2 == 0))
        {
            ledPin.setPixelColor(i, CRITICAL_COLOR);
        }
        else
        {
            ledPin.setPixelColor(i, ledPin.Color(100, 0, 0));
        }
    }
    ledPin.show();
    vTaskDelay(pdMS_TO_TICKS(despeed*100));
    currentStep++;
    currentStep = currentStep%2;
    
}

//fixen
void LEDAnimation::updateStartup() {
    uint32_t currentTime = xTaskGetTickCount() * portTICK_PERIOD_MS;

    ledPin.setPixelColor(currentStep, color);
    vTaskDelay(pdMS_TO_TICKS(despeed*10));
    ledPin.show();

    currentStep++;

    if(currentStep == count)
    {
        activateStatic();
    }
}


void LEDAnimation::updateRotating() {
    uint32_t currentTime = xTaskGetTickCount() * portTICK_PERIOD_MS;
    
    ledPin.clear();
    ledPin.setPixelColor(currentStep, color);

    if(currentStep == count)
    {
        ledPin.setPixelColor(0, color);
    }
    else
    {
        ledPin.setPixelColor(currentStep + 1, color);
    }

    if(currentStep == 0)
    {
        ledPin.setPixelColor(count, color);
    }
    else
    {
        ledPin.setPixelColor(currentStep - 1, color);
    }
    ledPin.show();
    
    if(currentStep == count)
    {
        currentStep = 0;
    }
    else
    {
        currentStep++;
    }

    vTaskDelay(pdMS_TO_TICKS(despeed*10));
}


void LEDAnimation::updateConnection() {
    uint32_t currentTime = xTaskGetTickCount() * portTICK_PERIOD_MS;
    currentStep;
    setAll(color);
    if(currentStep <= 10)
    {
        ledPin.setBrightness(currentStep*10);
    }
    else
    {
        ledPin.setBrightness((20-currentStep)*10);
    }

    if(currentStep == 20)
    {
        currentStep = 0;
    }
    else
    {
        currentStep++;
    }
    vTaskDelay(pdMS_TO_TICKS(despeed*10));
}
