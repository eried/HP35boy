void get_f_l(char ws) {

  //("field selection = ");
  switch (word_select) {

    case 0:
      first = p;
      last = p;
      break;

    case 1:
      first = 3;
      last = 12;
      break;

    case 2:
      first = 0;
      last = 2;
      break;

    case 3:
      first = 0;
      last = 13;
      break;

    case 4:
      first = 0;
      last = p;
      break;

    case 5:
      first = 3;
      last = 13;
      break;

    case 6:
      first = 2;
      last = 2;
      break;

    case 7:
      first = 13;
      last = 13;
      break;

  }

  return;

}

byte do_add (byte x, byte y)  {
  int res;
  res = x + y + carry;
  if (res > 9) {
    res -= 10;
    carry = 1;
  } else
    carry = 0;
  return (byte) res;
}

byte do_sub (byte x, byte y)  {
  int res;
  res = (x - y) - carry;
  if (res < 0) {
    res += 10;
    carry = 1;
  }
  else
    carry = 0;
  return (byte) res;
}
