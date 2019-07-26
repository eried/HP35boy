#include <Arduboy2.h>
#include "avr/pgmspace.h"
#include <TimerOne.h>

// Based on HP35 emulator http://home.citycable.ch/pierrefleur/Jacques-Laporte/HP35_Arduino.htm check license in rom.h
#include "rom.h"
#include "registers.h"

#include "bitmaps.h"

Arduboy2 arduboy;
Sprites sprites;

#define SSIZE 12
#define WSIZE 14

int i, tm;
int io_count = 2;
boolean display_enable = true;
boolean update_display = true;

boolean enable_bug = false;
