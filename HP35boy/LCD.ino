void lcd_HP35()
{
  //lcd.clear();
  arduboy.clear();
  //arduboy.println("HP35 EMU");
  arduboy.drawBitmap(0, 0, hp35, 128, 64, WHITE);
  arduboy.display();

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

  arduboy.display();
  chr_prtd++;
}
