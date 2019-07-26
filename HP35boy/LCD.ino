int keyboardSelectByCode(byte keycode)
{
  for (int i = 0; i < totalKeys; i++)
    if (keyboard[i].keycode == keycode)
      return i;
  return 0;
}

int keyboardSelectByPosition(byte pos) // 0,1,2,3 up  right down  left
{
  return keyboardSelectByCode(keyboard[currentKey].near_keycode[pos]);
}

void lcd_init(bool powered = true)
{
  //lcd.clear();
  arduboy.clear();
  //arduboy.println("HP35 EMU");
  arduboy.drawBitmap(0, 0, hp35, 128, 64, WHITE);

  // Power switch
  byte x = powered ? 45 : 49;
  arduboy.drawLine(10, x, 10, x + 4);

  if (powered)
  {
    // Draw selection
    byte ix = keyboard[currentKey].x;
    byte iy = keyboard[currentKey].y;
    byte iw = 11;
    byte ih = keyboard[currentKey].size;
    //arduboy.fillCircle(, keyboard[currentKey].y, 3);

    // get buffer
    for (uint8_t x = ix; x < ix + iw; x++)
      for (uint8_t y = iy; y < iy + ih; y++)
        arduboy.drawPixel(x, y, !arduboy.getPixel(x, y));
  }
  arduboy.display();
}

void lcd_HP35()
{
  lcd_init();
  chr_prtd = 0;
  for (i = WSIZE - 1; i >= 0; i--)
  {
    //wwww
    if (b [i] >= 8) {
      print_lcd(' ');
    } else if (i == 2) {
      if (a [i] >= 8) {
        print_lcd('-');
      } else {
        print_lcd(' ');
      }
    }
    else if (i == 13) {
      if (a [i] >= 8) {
        print_lcd('-');
      }
      else {
        print_lcd(' ');
      }
    }
    else {
      print_lcd(a[i] + 48);
    }
    if (b [i] == 2) {

      print_lcd('.');
    }
  }

  arduboy.display();
}

void print_lcd(unsigned char m) {
  //lcd.print(m);
  //Serial.print((char)m);
  //arduboy.print((char)m);
  //
  bool space = false;

  if (m < '0' || m > '9')
    switch (m)
    {
      case '-':
        m = '9' + 1;
        break;

      case '.':
        m = '9' + 2;
        break;

      default:
        space = true;
        break;
    }

  if (!space)
    sprites.drawSelfMasked(0, 60 - (chr_prtd * 4), font, m - '0');
  chr_prtd++;
}
