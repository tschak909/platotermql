/**
 * PLATOTerm64 - A PLATO Terminal for the Commodore 64
 * Based on Steve Peltz's PAD
 * 
 * Author: Thomas Cherryhomes <thom.cherryhomes at gmail dot com>
 *
 * io.h - Input/output functions (serial/ethernet)
 */

#include <qdos.h>
#include "io.h"
#include "protocol.h"

chanid_t ser;
padByte buff[8192];
short len;

/**
 * io_init() - Set-up the I/O
 */
void io_init(void)
{
  mt_baud(1200);
  ser=io_open("SER",0);
}

/**
 * io_send_byte(b) - Send specified byte out
 */
void io_send_byte(unsigned char b)
{
  io_sbyte(ser,0,b);
}

/**
 * io_main() - The IO main loop
 */
void io_main(void)
{
  char ch;

  while (io_pend(ser,0)==0)
    {
      io_fbyte(ser,-1,&ch);
      buff[len++]=ch;
    }
  
  ShowPLATO(buff,len);
  len=0;
}

/**
 * io_done() - Called to close I/O
 */
void io_done(void)
{
}
