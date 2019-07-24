// HP35 emulator http://home.citycable.ch/pierrefleur/Jacques-Laporte/HP35_Arduino.htm

/*
  Copyright (c) 2011 DE LUCA Pietro, Italy
  $Id:hp35_lcd.pde 11-06-2011 Pietro $

  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    The name of the author may not be used to endorse or promote products derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE AUTHOR â€œAS ISâ€ AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "avr/pgmspace.h"
#include <TimerOne.h>
//byte rom[768]; ROM HP-35 Version V4.00 (validata) 32 caratteri per riga

PROGMEM const byte rom[] =
{ 0, 221, 2, 255, 2, 36, 0, 23, 1, 68, 2, 68, 0, 132, 1, 16, 2, 209, 3, 251, 0, 95, 0, 195, 1, 168, 3, 103, 2, 238, 3, 226,
  0, 46, 0, 144, 3, 234, 3, 234, 3, 234, 0, 107, 2, 105, 0, 168, 2, 168, 0, 255, 3, 234, 3, 234, 3, 234, 0, 48, 0, 204, 0, 170,
  1, 168, 0, 67, 1, 211, 0, 204, 0, 48, 0,  0, 0, 131, 1, 68, 0, 68, 0, 187, 2, 68, 0, 159, 2, 132, 3, 11, 0, 46, 0, 144,
  3, 40, 3, 111, 3, 234, 3, 234, 3, 234, 0, 75, 2, 103, 3, 168, 1, 113, 3, 119, 3, 203, 2, 206, 0, 196, 1, 219, 1, 40, 0, 52,
  2, 206, 3, 117, 1, 46, 2, 250, 1, 22, 3, 106, 3, 131, 1, 186, 3, 155, 3, 54, 3, 76, 3, 155, 0, 28, 1, 234, 0,  2, 1, 51,
  2, 196, 2, 214, 3, 166, 1, 20, 2, 31, 1, 125, 3, 119, 0, 210, 1, 114, 0, 218, 3, 138, 1, 119, 0, 206, 0, 52, 1, 142, 3, 12,
  1, 42, 1, 138, 1, 186, 1, 163, 0, 170, 1, 122, 1, 95, 1, 76, 3, 170, 1, 20, 1, 11, 3, 42, 0, 42, 3, 221, 1, 10, 2, 206,
  3, 44, 2, 39, 3, 178, 1, 235, 2, 209, 0, 144, 1, 20, 3, 219, 3, 178, 0, 250, 1, 142, 1, 186, 1, 255, 0, 218, 0, 170, 3, 76,
  1, 22, 1, 106, 2, 126, 1, 59, 2, 118, 2,  3, 0, 202, 3, 221, 2, 214, 1, 158, 3, 44, 2, 79, 0, 142, 1, 238, 0, 76, 1, 18,
  0, 60, 1, 162, 2, 63, 3, 174, 0, 236, 3, 231, 0, 202, 1, 132, 1, 235, 0, 254, 1, 168, 0, 46, 3, 250, 3, 250, 1, 250, 1, 250,
  0, 74, 2, 143, 3, 174, 3, 166, 1, 166, 2, 159, 3, 174, 2, 38, 0, 74, 2, 251, 2, 142, 3, 234, 0, 14, 2, 251, 2, 163, 2, 246,
  0, 212, 2, 211, 3, 126, 0, 254, 1, 212, 2, 223, 1, 40, 1, 196, 0, 206, 1, 110, 0, 190, 1, 254, 2, 46, 0, 48, 0, 144, 1, 113,
  1, 68, 3, 119, 2, 206, 1, 158, 2, 36, 3, 63, 1, 250, 2,  4, 1, 84, 3, 55, 1, 234, 3, 27, 0, 40, 0, 20, 3, 31, 0, 36,
  0, 28, 3, 44, 3, 67, 2, 40, 2, 20, 3, 51, 1, 14, 1, 100, 0, 208, 1, 40, 3, 174, 1, 117, 1, 196, 3, 221, 2, 189, 2, 43,
  2, 214, 0, 28, 0, 172, 1, 23, 3, 12, 2, 238, 2, 246, 3, 226, 3, 226, 0, 140, 0, 60, 3, 98, 3, 191, 0,  2, 3, 171, 3, 226,
  3, 46, 0, 48, 1,  4, 2, 212, 0, 115, 1, 191, 0, 254, 2, 164, 3, 15, 1, 148, 3, 243, 0, 28, 2, 146, 1, 233, 2, 168, 3, 111,
  3, 207, 3, 46, 0, 161, 1, 168, 0, 161, 1, 168, 2, 84, 0, 39, 3, 174, 1, 84, 0, 75, 0, 222, 2, 153, 1, 40, 2, 149, 2, 97,
  0, 149, 1, 168, 2, 153, 2, 148, 3, 107, 2, 238, 3, 226, 1, 38, 3, 166, 1, 106, 2, 146, 1, 186, 0, 103, 2, 210, 1, 234, 0, 119,
  2, 206, 2, 142, 1, 40, 2, 46, 1,  7, 2, 46, 1, 12, 3, 123, 1, 40, 3, 174, 1, 162, 0, 183, 0, 174, 1, 142, 0, 138, 3, 47,
  1, 142, 0, 84, 0, 151, 2, 148, 1, 183, 1, 84, 0, 87, 0, 254, 3, 190, 0, 55, 2, 146, 3, 126, 0, 235, 1, 254, 3, 50, 1, 210,
  3, 46, 1, 46, 3, 82, 0, 239, 1, 168, 2, 206, 3, 178, 3, 46, 1, 18, 1, 40, 3, 254, 3, 254, 0, 143, 0, 206, 0, 42, 2, 214,
  2, 201, 1, 98, 1, 168, 3, 174, 1, 12, 2, 145, 1, 140, 2, 109, 2, 12, 2, 109, 0, 140, 2, 24, 2, 140, 2, 109, 2, 57, 2, 109,
  3, 49, 1, 14, 2, 109, 0, 142, 3, 45, 3, 49, 2, 174, 2, 153, 2, 84, 1, 179, 0, 254, 2, 97, 0, 100, 0, 206, 1, 98, 1, 234,
  0, 84, 2, 151, 2, 153, 3, 49, 2, 174, 2, 149, 3, 49, 2, 174, 2, 174, 2, 85, 2, 174, 3, 173, 3, 49, 2, 140, 2, 113, 2, 57,
  2, 12, 2, 117, 0, 140, 2, 24, 1, 140, 2, 113, 1, 12, 2, 113, 2, 113, 3, 46, 2, 78, 3, 76, 1, 88, 3, 239, 1, 140, 2, 24,
  1, 152, 1, 88, 0, 152, 1, 24, 2, 88, 0, 84, 3, 107, 0, 48, 2, 238, 3, 226, 0, 16, 1, 16, 1, 14, 2, 150, 2, 46, 2, 135,
  1, 254, 3, 14, 2, 131, 3, 142, 1, 16, 1, 16, 1, 74, 1, 16, 1, 226, 3, 78, 2, 163, 3, 206, 1, 14, 0, 28, 2, 82, 0, 44,
  2, 167, 0, 183, 1, 226, 3, 22, 2, 203, 3, 150, 1, 22, 0, 28, 0, 44, 2, 207, 0, 183, 0, 28, 3, 150, 3, 111, 0, 16, 1, 122,
  1, 122, 2, 234, 3, 94, 2, 126, 3, 27, 1, 16, 2,  6, 3, 43, 0, 254, 3, 46, 3, 14, 1, 16, 0, 206, 2, 204, 1, 216, 2, 24,
  1, 88, 0, 216, 2, 88, 2, 24, 0, 88, 1, 152, 0, 216, 1, 88, 3, 12, 0, 48, 0, 16, 3, 138, 3, 123, 1, 98, 1, 254, 0, 44,
  2, 239, 3, 170, 2, 234, 0, 98, 3, 155, 2, 206, 2, 78, 2, 42, 0, 202, 3, 12, 2, 187, 1, 16, 2, 146, 2, 146, 1, 126, 3, 179,
  1, 210, 3, 18, 2, 50, 0, 142, 3, 126, 3, 187, 3, 178, 1, 168, 0, 30, 0,  7, 1, 14, 3, 178, 1, 40, 2, 146, 1, 126, 2, 62,
  0, 16, 3, 62, 3, 254, 2, 86, 1, 18, 0, 75, 1, 168, 2, 153, 1, 142, 2, 20, 1, 11, 2, 238, 3, 70, 0,  3, 2, 206, 1, 126,
  0,  3, 1, 254, 1, 46, 2, 89, 3, 98, 0, 71, 3, 50, 3, 158, 0,  7, 1, 204, 1, 181, 2, 12, 2, 117, 2, 76, 2, 113, 3, 249,
  2, 140, 2, 113, 1, 245, 2, 204, 2, 113, 3, 125, 2, 113, 2, 229, 2, 113, 3, 217, 3, 174, 1, 78, 0, 26, 0, 191, 1, 78, 3, 46,
  0, 28, 1, 14, 0, 108, 0, 195, 3, 174, 1, 190, 0, 227, 0, 230, 1, 234, 2, 204, 3, 21, 2, 84, 0, 27, 1, 84, 2, 83, 3, 217,
  2, 157, 2, 83, 3, 217, 3, 177, 2, 229, 2, 204, 2, 109, 3, 125, 2, 140, 2, 109, 1, 245, 2, 76, 2, 109, 3, 249, 2, 12, 2, 109,
  2, 109, 2, 109,
  //             0,0,0,0,     //versione   con bug e^ln(2.02)=2      if you uncomment this line ,comment the next line your pocket calculator is with bug
  1, 140, 2, 242,  //versione senza bug e^ln(2.02)=2.02   if you uncomment this line ,comment line before your pocket calculator is now perfect (no bug)
  3, 76, 2, 46, 3, 174, 1, 152, 2, 59, 0, 148, 1, 123, 3, 234, 2, 122, 3, 11, 3, 22, 1, 103,
  3, 150, 1, 14, 1, 106, 1, 115, 2, 206, 0, 210, 3, 170, 1, 190, 1, 179, 3, 46, 3, 14, 0, 238, 2, 206, 2, 46, 0, 206, 1, 102,
  0, 148, 1, 219, 1, 24, 1, 230, 1, 231, 1, 152, 0, 108, 1, 215, 2, 78, 2, 78, 0, 148, 2, 83, 0, 48, 1, 204, 0, 216, 0, 216,
  0, 24, 2, 24, 1, 88, 0, 24, 2, 88, 3, 171, 2, 89, 3, 226, 1, 46, 1, 126, 2, 27, 2, 210, 3, 174, 1, 22, 3, 174, 3, 126,
  2, 35, 3, 46, 3, 226, 3, 49, 0, 144, 2, 210, 3, 126, 2, 87, 2, 254, 3, 142, 0, 48, 0, 144, 2, 206, 2, 46, 2, 131, 3, 142,
  1, 126, 2, 127, 3, 174, 1, 22, 3, 174, 1, 183, 0, 204, 1, 202, 1, 94, 2, 175, 0, 190, 3, 38, 2, 238, 3, 44, 3, 23, 0, 102,
  2, 219, 0, 84, 0,  3, 0, 146, 3, 102, 1, 250, 2, 50, 3, 166, 0, 144, 2, 36, 1, 152, 2, 88, 0, 216, 0, 88, 1, 24, 1, 216,
  0, 88, 3, 155, 3, 230, 1, 147, 3, 142, 1, 98, 3, 19, 2, 206, 0, 60, 3, 108, 3, 23, 1, 234, 2, 254, 3, 12, 0, 46, 2, 98,
  3, 91, 1, 14, 1, 106, 2, 110, 3, 63, 0, 206, 1, 42, 3, 142, 2, 126, 3, 31, 3, 166, 1, 142, 0, 46, 3, 12, 1, 235, 2, 76,
  0, 216, 0, 88, 0, 24, 0, 88, 1, 216, 2, 88, 2, 24, 0, 24, 1, 88, 1, 88, 0, 216, 3, 119, 3, 174, 1, 46, 1, 134, 2, 186,
  1, 123, 1, 250, 2, 206, 1, 234, 3, 203, 1, 159, 0, 206, 3, 12, 0, 152, 0, 216, 0, 24, 0, 152, 1, 88, 2,  7, 1, 76, 1, 251
};


#define SSIZE 12
#define WSIZE 14
//#define LCD1x16 true  // otherwise is .... LCD 2 x 16 always 2 line (2x8) or (2x16) one IC 44780
// only the upper row work obviously whem use LCD (2x16)
// false design a LCD 2 x 16

//registri cpu
unsigned char a[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //56 bit +2 nibble (nota bene l'indice arriva a 15 !!!!!
unsigned char b[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //56 bit +2 nibble (nota bene l'indice arriva a 15 !!!!!
unsigned char c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //56 bit +2 nibble (nota bene l'indice arriva a 15 !!!!!
unsigned char d[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //56 bit +2 nibble (nota bene l'indice arriva a 15 !!!!!
unsigned char e[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //56 bit +2 nibble (nota bene l'indice arriva a 15 !!!!!
unsigned char f[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //56 bit +2 nibble (nota bene l'indice arriva a 15 !!!!!
unsigned char m[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //56 bit +2 nibble (nota bene l'indice arriva a 15 !!!!!
unsigned char t[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //56 bit temporary
unsigned char s[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ; //12 bit Status da S0 a S11
unsigned char p = 0;
unsigned char pc = 0;
unsigned char offset = 0;
unsigned char ret = 0;
unsigned char temp;
unsigned char first;
unsigned char last;
unsigned char zero = 0;
unsigned char carry = 0;
unsigned char prevCarry = 0;
unsigned char fetch_h;
unsigned char fetch_l;
unsigned char ROM = 0;
unsigned char op_code = 0;
unsigned char word_select = 0;
unsigned char key_code = -1;
unsigned char key_rom = 0;
unsigned char display_status = 0;
unsigned char error = 0;
unsigned char chr_prtd = 0;
int ledPin = 13;
boolean toggle;


int i, tm;
int io_count = 2;
boolean display_enable = true;
boolean update_display = true;

/*LCD4Bit lcd = LCD4Bit(2);
  const int DataPin = 5;
  const int IRQpin =  3;
  PS2Keyboard_1 keyboard;*/

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
