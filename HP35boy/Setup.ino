void setup() {

  pinMode(ledPin, OUTPUT);
  /*keyboard.begin(DataPin, IRQpin);
    lcd.init();

    lcd.clear();*/
  Timer1.initialize(100000);         //lampeggio 1/2 secondo
  Timer1.attachInterrupt(FlashLed);
  Timer1.stop();
  digitalWrite(ledPin, LOW);
}
