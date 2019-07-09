/**
 * PLATOTerm64 - A PLATO Terminal for the Commodore 64
 * Based on Steve Peltz's PAD
 * 
 * Author: Thomas Cherryhomes <thom.cherryhomes at gmail dot com>
 *
 * screen.h - Display output functions
 */

#ifndef SCREEN_H
#define SCREEN_H

#include <qdos.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "splash.h"
#include "protocol.h"
#include "font.h"

#define X_SCALE 0.29
#define Y_SCALE 0.1953125

extern padBool FastText; /* protocol.c */
extern padPt TTYLoc;

chanid_t win;
unsigned char CharWide=8;
unsigned char CharHigh=16;
padPt TTYLoc;

unsigned char current_background=0;
unsigned char current_foreground=3;

/**
 * screen_convert_coord(Coord) - scale coordinates.
 */
void screen_convert_coord(padPt* coord)
{
  coord->x=ceil(coord->x*X_SCALE);
  coord->y=ceil(coord->y*Y_SCALE);
}

/**
 * screen_splash - Show splash screen
 */
void screen_splash(void)
{
  ShowPLATO(splash,sizeof(splash));
}

/**
 * screen_init() - Set up the screen
 */
void screen_init(void)
{
  char hello[5]="Hello";
  win=io_open("CON_512x256a0x0",0);
  sd_setin(win,-1,7);
  sd_clear(win,-1);
  screen_splash();
}

/**
 * screen_update_colors() - Set the terminal colors
 */
void screen_update_colors(void)
{
}

/**
 * screen_wait(void) - Sleep for approx 16.67ms
 */
void screen_wait(void)
{
}

/**
 * screen_beep(void) - Beep the terminal
 */
void screen_beep(void)
{
}

/**
 * screen_clear - Clear the screen
 */
void screen_clear(void)
{
  sd_clear(win,-1);
}

/**
 * screen_set_pen_mode()
 * Set the pen mode based on CurMode.
 */
void screen_set_pen_mode(void)
{
}

/**
 * screen_block_draw(Coord1, Coord2) - Perform a block fill from Coord1 to Coord2
 */
void screen_block_draw(padPt* Coord1, padPt* Coord2)
{
}

/**
 * screen_dot_draw(Coord) - Plot a mode 0 pixel
 */
void screen_dot_draw(padPt* Coord)
{
}

/**
 * screen_line_draw(Coord1, Coord2) - Draw a mode 1 line
 */
void screen_line_draw(padPt* Coord1, padPt* Coord2)
{
  sd_line(win,
	  -1,
	  (Coord1->x)*X_SCALE,
	  (Coord1->y)*Y_SCALE,
	  (Coord2->x)*X_SCALE,
	  (Coord2->y)*Y_SCALE);
}

/**
 * screen_char_draw(Coord, ch, count) - Output buffer from ch* of length count as PLATO characters
 */
void screen_char_draw(padPt* Coord, unsigned char* ch, unsigned char count)
{
  sd_setsz(win,-1,1,0);
  sd_gcur(win,
  	  -1,
  	  (double)0.0,
  	  (double)0.0,
  	  (double)(Coord->y+16)*Y_SCALE,
  	  (double)Coord->x*X_SCALE);

  
  io_sstrg(win,
  	   -1,
  	   ch,
  	   count);
}

/**
 * screen_tty_char - Called to plot chars when in tty mode
 */
void screen_tty_char(padByte theChar)
{
  io_sbyte(win,-1,theChar);
}

/**
 * screen_foreground - set foreground color
 */
void screen_foreground(padRGB* theColor)
{
}

/**
 * screen_background - set background_color
 */
void screen_background(padRGB* theColor)
{
}

/**
 * screen_paint - Paint the screen
 * Calling convention is different due to this needing to be recursive.
 */
void screen_paint(padPt* Coord)
{
}

/**
 * screen_done()
 * Close down TGI
 */
void screen_done(void)
{
}

#endif /* SCREEN_H */
