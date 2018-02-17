class Button {
private:
    int g_pin;
    long millisHeld;
    unsigned long firstTimePushed;
    int previousState;

public:
    Button(int pin);
    int getState();
    int check();
};
