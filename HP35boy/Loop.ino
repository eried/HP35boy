
void loop() {



  prevCarry = carry;
  carry = 0;
  fetch_h = 0;
  fetch_l = 0;
  fetch_h = pgm_read_byte_near (rom + ( offset * 256 * 2 ) + (pc * 2)    );
  fetch_l = pgm_read_byte_near (rom + ( offset * 256 * 2 ) + (pc * 2) + 1 );

  if ((pc == 191) & (offset == 0)) {
    error = 1;
  }

  if (error == 1) {
    Timer1.start();
  }


  pc++;
  pc %= 256;

  //ulteriore elaborazione del tasto ricevuto
  if (key_code < 255) {
    error = 0;
    Timer1.stop();
    digitalWrite(ledPin, LOW);

    key_rom = key_code;

    key_code = -1;
    s[0] = 1;
  }

  //Classifico le istruzioni per tipo

  if (fetch_l == 0x00) {

    //NOP
  }

  if ((fetch_l & 0x03) == 0x01) {
    //Jump subroutine


    ret = pc;
    pc = (((fetch_l >> 2) & 0x3f) | ((fetch_h << 6) & 0x0c0));

  }

  if ((fetch_l & 0x7F) == 0x030) {
    //("Return from Subroutine");

    pc = ret;
  }

  if ((fetch_l & 0x7F) == 0x010) {
    // ("Select ROM");

    offset = (       ((fetch_h << 1) & 06)   |    ((fetch_l >> 7) & 01)      );

  }

  //testa se Ã¨ diponibile un carattere da tastiera
  //se si lo inserisce nel buffer e setta ad 1 la variabile key
  //la cpu fa un salto incondizionato all'indirizzo pc+rom (istruzione keyrom)
  if (fetch_l == 0x0D0) {
    pc = key_rom;
    //resetta s0 non controlla se era ad 1 prima
    s[0] = 0;
    // ("KEYROM");

  }

  //routine di servizio che legge i dati in input


  /*if (keyboard.available()) {
    char c = keyboard.read();

    switch (c) {
      case '0':
        key_code = 36;
        break;

      case '1':
        key_code = 28;
        break;

      case '2':
        key_code = 27;
        break;

      case '3':
        key_code = 26;
        break;

      case '4':
        key_code = 20;
        break;

      case '5':
        key_code = 19;
        break;

      case '6':
        key_code = 18;
        break;

      case '7':
        key_code = 52;
        break;

      case '8':
        key_code = 51;
        break;

      case '9':
        key_code = 50;
        break;

      case PS2_ENTER:
        key_code = 62;
        break;

      case PS2_SF7: //1/x
        key_code = 14;
        break;

      case PS2_SF9: //SIN
        key_code = 43;
        break;

      case PS2_SF10: //COS
        key_code = 42;
        break;

      case PS2_SF11: //TAN
        key_code = 40;
        break;

      case PS2_SF12: //PI
        key_code = 34;
        break;

      case PS2_F1: //CHS
        key_code = 59;
        break;

      case PS2_F2: //EEX
        key_code = 58;
        break;

      case PS2_F3: //x<->Y
        key_code = 12;
        break;
      // |
      case PS2_F4: //Rv
        key_code = 11;
        break;

      case PS2_F5: //STO
        key_code = 10;
        break;

      case PS2_F6: //RCL
        key_code = 8;
        break;

      case PS2_F7: //X^Y
        key_code = 6;
        break;

      case PS2_F8: //log
        key_code = 4;
        break;

      case PS2_F9: //ln
        key_code = 3;
        break;

      case PS2_F10: //e^x
        key_code = 2;
        break;

      case PS2_F11: //SQR(x)
        key_code = 46;
        break;

      case PS2_F12: //ARC
        key_code = 44;
        break;

      case '+':
        key_code = 22;
        break;

      case '-':
        key_code = 54;
        break;

      case '/':
        key_code = 38;
        break;

      case '*':
        key_code = 30;
        break;

      case '.':
        key_code = 35;
        break;

      case PS2_SESC:
        key_code = 0; //CLR
        break;

      case PS2_ESC:
        key_code = 56; //CLX
        break;

      default:
        key_code = -1;
    }
  }*/

  //*********************************************************

  if ((fetch_l & 0x03f) == 0x014) {
    //testa il bit n dello status( copia il bit nel carry)
    // ("Test bit n dello Status ");

    carry = s[ ((fetch_h & 0x03) << 2)  | ( (fetch_l & 0x0c0) >> 6) ];
  }


  if ((fetch_l & 0x03f) == 0x004) {
    //setta il bit n dello status
    // ("Set bit n dello Status ");

    s[ ((fetch_h & 0x03) << 2)  | ( (fetch_l & 0x0c0) >> 6) ] = 1;
  }

  if ((fetch_l & 0x03f) == 0x024) {
    //resetta il bit n dello status
    // ("ReSet bit n dello Status ");

    s[ ((fetch_h & 0x03) << 2)  | ( (fetch_l & 0x0c0) >> 6) ] = 0;
  }

  if ((fetch_l & 0x03f) == 0x034) {
    //resetta tutti i bit dello status
    // ("Cancella tutti bit dello Status ");
    for (i = 0; i <= 12; i++) s[i] = 0;
  }

  //*********************************************************



  //*********************************************************

  if ((fetch_l & 0x03f) == 0x02C) {
    //testa il bit n dello status( copia il bit nel carry)
    // ("Test se P=numero N carry = 1 ");

    carry = 0;
    if (p == (((fetch_h & 0x03) << 2)  | ( (fetch_l & 0x0c0) >> 6)) ) carry = 1;
  }


  if ((fetch_l & 0x03f) == 0x00C) {
    //setta il bit n dello status
    //("Set Pointer con n ");

    p = (((fetch_h & 0x03) << 2)  | ( (fetch_l & 0x0c0) >> 6) );
  }

  if ((fetch_l & 0x03f) == 0x03C) {
    //resetta il bit n dello status
    //("Incrementa P ");

    p = ((p + 1) & 0x0f);
  }

  if ((fetch_l & 0x03f) == 0x01C) {
    //resetta tutti i bit dello status
    //("Decrementa P ");
    p = ((p - 1) & 0x0f);
  }
  //*********************************************************

  //*********************************math operation
  //*******************************************************

  if ((fetch_l & 0x3F) == 0x18) {
    //Data entry - Display
    //("Load Costant");
    //function loadconst(num) { return function () { c[p] = num; p = (p - 1) & 0xf; }; }
    c[p] = ((fetch_l >> 6) | (fetch_h << 2));
    p = ( (p - 1) & 0x0f);
  }


  if (((fetch_h & 0x03) == 0x00) && ((fetch_l & 0x0ef) == 0x0A8)) {
    //exch_m
    for (i = 0; i < WSIZE; i++)

    {

      tm = c [i]; c [i] = m[i]; m [i] = tm;

    }
  }
  if (((fetch_h & 0x03) == 0x01) && ((fetch_l & 0x0ef) == 0x028)) {
    //c_to_stack
    for (i = 0; i < WSIZE; i++)

    {

      f [i] = e [i];

      e [i] = d [i];

      d [i] = c [i];

    }

  }
  if (((fetch_h & 0x03) == 0x01) && ((fetch_l & 0x0ef) == 0x0A8)) {
    //stack_to_a
    for (i = 0; i < WSIZE; i++)

    {

      a [i] = d [i];

      d [i] = e [i];

      e [i] = f [i];

    }
  }
  if (((fetch_h & 0x03) == 0x02) && ((fetch_l & 0x0ef) == 0x0A8)) {
    //m_to_c
    for (i = 0; i < WSIZE; i++)

      c [i] = m [i];
  }
  if (((fetch_h & 0x03) == 0x03) && ((fetch_l & 0x0ef) == 0x028)) {
    //down_rotate
    for (i = 0; i < WSIZE; i++)

    {

      tm = c [i];

      c [i] = d [i];

      d [i] = e [i];

      e [i] = f [i];

      f [i] = tm;

    }
  }
  if (((fetch_h & 0x03) == 0x03) && ((fetch_l & 0x0ef) == 0x0A8)) {
    //clear_reg
    for (i = 0; i < WSIZE; i++)
      a [i] = b [i] = c [i] = d [i] = e [i] = f [i] = m [i] = 0;

  }



  if (((fetch_h & 0x03) == 0x00) && ((fetch_l & 0x0ef) == 0x028)) {
    display_enable = false;
    update_display =  false;

  }



  if (((fetch_h & 0x03) == 0x02) && ((fetch_l & 0x0ef) == 0x028)) { //display toggle
    display_enable = ! display_enable;
    if (display_enable == true) {
      update_display = true;

    }
  }








  if ((fetch_l & 0x03) == 0x03) {
    //salto condizionale
    //("Conditional Branch --> ");




    if ( prevCarry != 1) {
      pc = ((fetch_l & 0x0fc) >> 2)  | ( (fetch_h & 0x03) << 6);
    }
  }

  if ((fetch_l & 0x03) == 0x02) {
    //A&R
    word_select = ((fetch_l >> 2) & 0x07);
    op_code = ((fetch_l >> 5) & 0x07);
    op_code = op_code | ((fetch_h << 3) & 0x018);

    get_f_l(word_select);

    switch (op_code) {

      case 0x0:
        //("A&R 0+B");
        carry = 0; //
        for (i = first; i <= last; i++)
          carry |= (b[i] != 0) ? 1 : 0;
        break;

      case 0x01:
        //("A&R 0->B");

        for (i = first; i <= last; i++) {
          b[i] = 0;
        }
        carry = 0;
        break;

      case 0x02:
        // ("A&R A-C");
        carry = 0;
        for (i = first; i <= last; i++)
          t[i] = do_sub (a[i], c[i]);
        break;

      case 0x03:
        //  ("A&R C-1");
        carry = 1;
        for (i = first; i <= last; i++)
          carry &= (c[i] == 0) ? 1 : 0;
        break;



      case 0x04:
        //("A&R B->C");

        for (i = first; i <= last; i++) {
          c[i] = b[i];
        }
        carry = 0;
        break;

      case 0x05:
        //   ("A&R 0-C->C");
        carry = 0;
        for (i = first; i <= last; i++)
          c[i] = do_sub (zero, c[i]);

        break;


      case 0x06:
        //("A&R 0->C");

        for (i = first; i <= last; i++) {
          c[i] = 0;
        }
        carry = 0;
        break;

      case 0x07:
        //  ("A&R 0-C-1->C");
        carry = 1;
        for (i = first; i <= last; i++)
          c[i] = do_sub (zero, c[i]);
        break;

      case 0x08:
        //  ("A&R Sh A Left");
        for (i = last; i >= first; i--)
          a[i] = (i == first) ? 0 : a [i - 1];
        carry = 0;
        break;

      case 0x09:
        //("A&R A->B");

        for (i = first; i <= last; i++) {
          b[i] = a[i];
        }
        carry = 0;
        break;

      case 0x0a:
        //("A&R A-C->C");
        carry = 0;
        for (i = first; i <= last; i++)
          c [i] = do_sub (a [i], c [i]);
        break;

      case 0x0b:
        //   ("A&R C-1->C");
        carry = 1;
        for (i = first; i <= last; i++)
          c[i] = do_sub (c[i], zero);
        break;

      case 0x0c:
        //("A&R C->A");

        for (i = first; i <= last; i++) {
          a[i] = c[i];
        }
        carry = 0;
        break;

      case 0x0d:
        //  ("A&R 0-C");//influenza solo i flag


        for (i = first; i <= last; i++)
          carry |= (c[i] != 0) ? 1 : 0;
        break;


      case 0x0e:
        // ("A&R A+C->C");
        carry = 0;
        for (i = first; i <= last; i++)
          c[i] = do_add (a[i], c[i]);

        break;

      case 0x0f:
        //    ("A&R C+1->C");
        carry = 1;
        for (i = first; i <= last; i++)
          c[i] = do_add (c[i], zero);
        break;

      case 0x010:
        //  ("A&R A-B");

        for (i = first; i <= last; i++)
          t[i] = do_sub (a[i], b[i]);
        break;

      case 0x011:
        // ("A&R B<->C");

        for (i = first; i <= last; i++) {
          temp = b[i];
          b[i] = c[i];
          c[i] = temp;
        }
        carry = 0;
        break;

      case 0x012:
        //    ("A&R Sh C Right");
        for (i = first; i <= last; i++)
          c[i] = (i == last) ? 0 : c [i + 1];
        carry = 0;
        break;

      case 0x013:
        //  ("A&R A-1");
        carry = 1;
        for (i = first; i <= last; i++)
          carry &= (a[i] == 0) ? 1 : 0;
        break;

      case 0x014:
        //  ("A&R Sh B Right");
        for (i = first; i <= last; i++)
          b[i] = (i == last) ? 0 : b [i + 1];
        carry = 0;
        break;

      case 0x015:
        // ("A&R C+C->A");
        carry = 0;
        for (i = first; i <= last; i++)
          c[i] = do_add (c[i], c[i]);
        break;


      case 0x016:
        //   ("A&R Sh A Right");
        for (i = first; i <= last; i++)
          a[i] = (i == last) ? 0 : a [i + 1];
        carry = 0;
        break;


      case 0x017:

        //("A&R 0->A");//ok

        for (i = first; i <= last; i++) {
          a[i] = 0;
        }
        carry = 0;
        break;

      case 0x018:
        // ("A&R A-B->A");
        carry = 0;
        for (i = first; i <= last; i++)
          a[i] = do_sub (a[i], b[i]);
        break;

      case 0x019:
        //("A&R A<->B");

        for (i = first; i <= last; i++) {
          temp = a[i];
          a[i] = b[i];
          b[i] = temp;
        }
        carry = 0;
        break;

      case 0x01a:
        // ("A&R A-C->A");

        carry = 0;
        for (i = first; i <= last; i++)
          a[i] = do_sub (a[i], c[i]);
        break;

      case 0x01b:
        //  ("A&R A-1->A");

        carry = 1;
        for (i = first; i <= last; i++)
          a[i] = do_sub (a[i], zero);
        break;

      case 0x01c:
        //("A&R A+B->A");

        carry = 0;
        for (i = first; i <= last; i++)
          a[i] = do_add (a[i], b[i]);
        break;

      case 0x01d:
        //("A&R C<->A");

        for (i = first; i <= last; i++) {
          temp = a[i];
          a[i] = c[i];
          c[i] = temp;
        }
        carry = 0;
        break;

      case 0x01e:
        // ("A&R A+C->A");

        carry = 0;
        for (i = first; i <= last; i++)
          a[i] = do_add (a[i], c[i]);
        break;

      case 0x01f:
        //  ("A&R A+1->A");

        carry = 1;
        for (i = first; i <= last; i++)
          a[i] = do_add (a[i], zero);
        break;
    }
    //A&R fine

  }


  //**************************************************************************
  //**************************************************************************
  //**************************************************************************
  //**************************************************************************
  if (display_enable) {

    update_display = true;
  }
  if (!display_enable) {

    if (update_display) {
      lcd_HP35();

      update_display = false;

    }
  }




}//fine ciclo loop

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



unsigned char codeKey(unsigned char key_code) {
  switch (key_code)  {
    // 0
    case 48:
      key_code = 36;
      break;
    // 1
    case 49:
      key_code = 28;
      break;
    // 2
    case 50:
      key_code = 27;
      break;
    // 3
    case 51:
      key_code = 26;
      break;
    // 4
    case 52:
      key_code = 20;
      break;
    // 5
    case 53:
      key_code = 19;
      break;
    // 6
    case 54:
      key_code = 18;
      break;
    // 7
    case 55:
      key_code = 52;
      break;
    // 8
    case 56:
      key_code = 51;
      break;
    // 9
    case 57:
      key_code = 50;
      break;
    // .
    case 46:
      key_code = 35;
      break;
    // +
    case 43:
      key_code = 22;
      break;
    // -
    case 45:
      key_code = 54;
      break;
    // *
    case 42:
      key_code = 30;
      break;
    // /
    case 47:
      key_code = 38;
      break;
    //ENTER con il tasto invio
    case 10:
      key_code = 62;
      break;
    //ENTER con il tasto #
    case 35:
      key_code = 62;
      break;

    //sin lettera s
    case 115:
      key_code = 43;
      break;
    //radice quadrata r
    case 114:
      key_code = 46;
      break;
    //pi greco
    case 112:
      key_code = 34;
      break;
    //clear
    case 99:

      key_code = 0;
      break;
    //arc

    case 97:
      key_code = 44;
      break;
      //default:
      //non fa nulla
  }
  return key_code;
}


void FlashLed()
{
  if (toggle)
    digitalWrite(ledPin, HIGH);
  if (!toggle)
    digitalWrite(ledPin, LOW);
  toggle = !toggle;


}
