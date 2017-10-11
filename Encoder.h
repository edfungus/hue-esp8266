class Encoder {
private:
  int gp_pin;
  int gn_pin;
  int gprevious;
  int gstep;
  int gmovement;

public:
  Encoder(int p_pin, int n_pin, int step);
  int getMovement();
  void clearMovement();
  void interrupt();
  void setupPins(void (*interruptDispatch)());
};
