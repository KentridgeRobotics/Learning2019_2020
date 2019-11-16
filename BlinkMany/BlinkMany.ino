class LED {
  public:
    int pin;
    int period;
    bool isLit;
    long lastChangeTime;
    
    LED(int thePin, int thePeriod) {
      pin = thePin;
      period = thePeriod;
      isLit = false;
      lastChangeTime = 0;
    }

    void doLoop(long currentTime) {
      if (currentTime > lastChangeTime + period) {
        if (isLit) {
          digitalWrite(pin, LOW);
        } else {
          digitalWrite(pin, HIGH);
        }
        isLit = !isLit;
        lastChangeTime = currentTime;
      }
    }
};

LED red(3, 1000);
LED yellow(5, 500);
LED green(6, 200);

void setup() {
  pinMode(red.pin, OUTPUT);
  pinMode(yellow.pin, OUTPUT);
  pinMode(green.pin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  long currentTime = millis();
  red.doLoop(currentTime);
  yellow.doLoop(currentTime);
  green.doLoop(currentTime);
}
