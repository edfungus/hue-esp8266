#include <Arduino.h>
#include "Encoder.h"

Encoder::Encoder(int p_pin, int n_pin, int step) {
    gp_pin = p_pin;
    gn_pin = n_pin;
    gstep = step;

    gmovement = 0;
    gprevious = 0;
}

int Encoder::getMovement() {
    return gmovement;
}

void Encoder::clearMovement() {
    gmovement = 0;
}

void Encoder::interrupt() {
    int pos = digitalRead(gp_pin);
    int neg = digitalRead(gn_pin);
    if(pos == 0 && neg == 0) {
        if(gprevious == 0b10){
            gmovement += 2;
        }
        if(gprevious == 0b01){
            gmovement -= 2;      
        }
    }
    gprevious = (pos << 1) | neg;
}

void Encoder::setupPins(void (*interruptDispatch)()) {
    pinMode(gp_pin, INPUT_PULLUP); 
    pinMode(gn_pin, INPUT_PULLUP); 
    attachInterrupt(gp_pin, interruptDispatch, FALLING);
    attachInterrupt(gn_pin, interruptDispatch, FALLING);
}
