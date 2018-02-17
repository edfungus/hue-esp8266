#include <Arduino.h>
#include "Button.h"

Button::Button(int pin) {
    g_pin = pin;
    previousState = LOW;
    pinMode(g_pin, INPUT);
}

int Button::getState() {
    return digitalRead(g_pin);;
}

// Return 0 = no change and no action
// Return 1 = short push
// Return 2 = long push
int Button::check() {
    int output = 0;
    int currentState = digitalRead(g_pin);

    if (currentState == HIGH && previousState == LOW && (millis() - firstTimePushed) > 200) {
        firstTimePushed = millis();
    }

    millisHeld = millis() - firstTimePushed;

    if (millisHeld > 50 && currentState == LOW && previousState == HIGH) {
        if (millisHeld <= 300) {
            output = 1;
        }
        if (millisHeld >= 300) {
            output = 2;
        }
        // Serial.println(millisHeld);
    }

    previousState = currentState;
    return output;
}
