void lcd_HP35() {
  //lcd.clear();
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
  chr_prtd++;
}
