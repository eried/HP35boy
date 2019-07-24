void setup() {

  // initiate arduboy instance
  arduboy.begin();

  // here we set the framerate to 15, we do not need to run at
  // default 60 and it saves us battery life
  arduboy.setFrameRate(15);

  //pinMode(ledPin, OUTPUT);
  /*keyboard.begin(DataPin, IRQpin);
    lcd.init();

    lcd.clear();*/

  Serial.begin(9600);

  Timer1.initialize(100000);         //lampeggio 1/2 secondo
  Timer1.attachInterrupt(FlashLed);
  Timer1.stop();
  digitalWrite(ledPin, HIGH);
}

boolean toggle;
void FlashLed()
{
  if (toggle)
    digitalWrite(ledPin, LOW);
  if (!toggle)
    digitalWrite(ledPin, HIGH);
  toggle = !toggle;
}
