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
#include "scale.h"

extern padBool FastText; /* protocol.c */
extern padPt TTYLoc;

chanid_t win;
unsigned char CharWide=8;
unsigned char CharHigh=16;
padPt TTYLoc;

unsigned char current_background=0;
unsigned char current_foreground=3;

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
  int ret;
  char hello[5]="Hello";
  win=io_open("CON_512x256a0x0",0);

  ret=sd_fount(win,-1,(char*)font,(char*)font);

  sd_setin(win,0,7);
  sd_clear(win,0);
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
  beep(110,10);
}

/**
 * screen_clear - Clear the screen
 */
void screen_clear(void)
{
  sd_clear(win,0);
}

/**
 * screen_set_pen_mode()
 * Set the pen mode based on CurMode.
 */
void screen_set_pen_mode(void)
{
  if (CurMode==ModeErase || CurMode==ModeInverse)
    {
      sd_setin(win,-1,0);
      sd_setpa(win,-1,7);
      sd_setst(win,-1,7);
      sd_setmd(win,-1,DM_OVER);
    }
  else
    {
      sd_setin(win,-1,7);
      sd_setpa(win,-1,0);
      sd_setst(win,-1,0);
      sd_setmd(win,-1,DM_OVER);
    }
}

/**
 * screen_block_draw(Coord1, Coord2) - Perform a block fill from Coord1 to Coord2
 */
void screen_block_draw(padPt* Coord1, padPt* Coord2)
{
  QLRECT_t r;
  colour_t c;

  screen_set_pen_mode();
  if (CurMode==ModeInverse || CurMode==ModeErase)
    c=0;
  else
    c=7;

  r.q_x=min(scalex[Coord1->x],scalex[Coord2->x]);
  r.q_y=min(scaley[Coord1->y],scalex[Coord2->y]);
  r.q_width=max(scalex[(Coord2->x-Coord1->x)], scalex[Coord1->x-Coord2->x]);
  r.q_height=max(scaley[(Coord2->y-Coord1->x)], scaley[Coord2->y-Coord1->y]);
  
  sd_fill(win,-1,c,&r);
}

/**
 * screen_dot_draw(Coord) - Plot a mode 0 pixel
 */
void screen_dot_draw(padPt* Coord)
{
  screen_set_pen_mode();
  sd_point(win,
	   0,
	   scalex[Coord->x],
	   scalex[Coord->y]);
}

/**
 * screen_line_draw(Coord1, Coord2) - Draw a mode 1 line
 */
void screen_line_draw(padPt* Coord1, padPt* Coord2)
{
  screen_set_pen_mode();
  sd_line(win,
	  0,
	  scalex[Coord1->x],
	  scaley[Coord1->y],
	  scalex[Coord2->x],
	  scaley[Coord2->y]);
}

/**
 * screen_char_draw(Coord, ch, count) - Output buffer from ch* of length count as PLATO characters
 */
void screen_char_draw(padPt* Coord, unsigned char* ch, unsigned char count)
{
  int i;
  int y_offset=16;
  char offset;
 
  switch (CurMem)
    {
    case M0:
      sd_fount(win,-1,(char*)font,(char*)font);
      offset=0;
      break;
    case M1:
      sd_fount(win,-1,(char*)font,(char*)font);
      offset=96;
      break;
    case M2:
      offset=-32;
      break;
    case M3:
      offset=32;
      break;
    }
  
  // Temporary: use m0/m1 font, todo, implement m2/m3
  
  switch (CurMode)
    {
    case ModeWrite:
      sd_setmd(win,-1,DM_OR);
      sd_setpa(win,-1,0);
      sd_setin(win,-1,7);
      break;
    case ModeRewrite:
      sd_setmd(win,-1,DM_OVER);
      sd_setpa(win,-1,0);
      sd_setin(win,-1,7);
      break;
    case ModeErase:
      sd_setmd(win,-1,DM_OR);
      sd_setpa(win,-1,0);
      sd_setin(win,-1,0);
      break;
    case ModeInverse:
      sd_setmd(win,-1,DM_OVER);
      sd_setpa(win,-1,7);
      sd_setin(win,-1,0);
      break;
    }
  
  if (ModeBold)
    {
      offset=32;
      sd_setsz(win,0,3,1);
    }
  else
    sd_setsz(win,0,1,0);

  sd_gcur(win,
  	  0,
  	  0.0,
  	  0.0,
  	  scaley[Coord->y+y_offset],
  	  scalex[Coord->x]);
  
  for (i=0;i<count;++i)
    ch[i]+=offset;
  
  io_sstrg(win,
  	   0,
  	   ch,
  	   count);
}

/**
 * screen_tty_char - Called to plot chars when in tty mode
 */
void screen_tty_char(padByte theChar)
{
  io_sbyte(win,0,theChar);
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
  /* TODO */
}

/**
 * screen_done()
 * Close down TGI
 */
void screen_done(void)
{
  /* TODO */
}

#endif /* SCREEN_H */
