/**
 * PLATOTerm64 - A PLATO Terminal for the Commodore 64
 * Based on Steve Peltz's PAD
 * 
 * Author: Thomas Cherryhomes <thom.cherryhomes at gmail dot com>
 *
 * keyboard.c - Keyboard functions
 */

#include <qdos.h>
#include "protocol.h"
#include "keyboard.h"
#include "io.h"

extern chanid_t win;

/**
 * keyboard_out - If platoKey < 0x7f, pass off to protocol
 * directly. Otherwise, platoKey is an access key, and the
 * ACCESS key must be sent, followed by the particular
 * access key from PTAT_ACCESS.
 */
void keyboard_out(unsigned char platoKey)
{
}

/**
 * keyboard_main - Handle the keyboard presses
 */
void keyboard_main(void)
{
  char ch;
  int ret;
  ret=io_fbyte(win,0,&ch);
  if (ret==0)
    {
      if (ch==0x0a)
	ch=0x0d;
      io_send_byte(ch);
    }
}

/**
 * keyboard_clear() - Clear the keyboard buffer
 */
void keyboard_clear(void)
{
}

/**
 * keyboard_out_tty - keyboard output to serial I/O in TTY mode
 */
void keyboard_out_tty(char ch)
{
}
