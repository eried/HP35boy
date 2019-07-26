void setup()
{
  arduboy.boot();
  arduboy.setFrameRate(15);
  Serial.begin(9600);

  Timer1.initialize(100000);         //lampeggio 1/2 secondo
  Timer1.attachInterrupt(FlashLed);
  Timer1.stop();
  digitalWrite(RED_LED, HIGH);

  // Fake power on
  currentKey = keyboardSelectByCode(62);
  lcd_init(false);
  delay(500);

  if (arduboy.pressed(B_BUTTON))
  {
    enable_bug = true;
    digitalWrite(BLUE_LED, LOW);
    while (arduboy.pressed(B_BUTTON));
    digitalWrite(BLUE_LED, HIGH);
  }
}

boolean toggle;
void FlashLed()
{
  if (toggle)
    digitalWrite(RED_LED, LOW);
  if (!toggle)
    digitalWrite(RED_LED, HIGH);
  toggle = !toggle;
}
