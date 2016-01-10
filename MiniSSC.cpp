//==============================================================================
// MiniSSC.cpp - MiniSSC II Communication Module
//
// Author        : Vilas Kumar Chitrakaran
// Version       : 2.0 (May 2005)
// Compatibility : POSIX, GCC
//==============================================================================
 
#include "MiniSSC.hpp"

//#define DEBUG

#ifdef DEBUG
 #include <string.h>
#endif

//==============================================================================
// MiniSSC::MiniSSC
//==============================================================================
MiniSSC::MiniSSC() 
{
 d_serialPort = 0;
}  
  
//==============================================================================
// MiniSSC::~MiniSSC
//==============================================================================
MiniSSC::~MiniSSC () 
{
 if (d_serialPort)
  close (d_serialPort);
}
  
//==============================================================================
// MiniSSC::reset
//==============================================================================
int MiniSSC::reset(const char *portName, bool ij, bool bj)
{
 if (d_serialPort)
  close (d_serialPort);

 speed_t baud;
 if(bj)
  baud = B9600;
 else
  baud = B2400;
  
 if ( (d_serialPort = open (portName, O_RDWR)) == -1) 
  return -1;

 // Set the parameters for the serial port.
 struct termios tops;
 tcgetattr (d_serialPort, &tops); // get the current attributes
 cfmakeraw(&tops); // set up for binary IO
 tops.c_cflag &= ~(IXON|IXOFF); // disable flow control
 cfsetispeed (&tops, baud); // set input baud rate
 cfsetospeed (&tops, baud); // set output baud rate
 tcsetattr (d_serialPort, TCSANOW, &tops); // set new attributes

#ifdef DEBUG
 memset(&tops, 0, sizeof(tops));
 tcgetattr(d_serialPort, &tops);
 baud = cfgetospeed( &tops);
 fprintf(stderr, "[MiniSSC::reset]: port %s, baud %d\n", portName, (int)baud);
#endif

 // Initialize SSC outputs
 char buf[3];
 buf[0] = 0xFF;
 buf[2] = 0x80;
 for (int ch = 0; ch < 8; ch++)
 {
  buf[1] = (char)ch;
  if ( (write(d_serialPort, buf, 3)) != 3 )
   return -1;
 }
 return 0;
}


//==============================================================================
// MiniSSC::actuate
//==============================================================================
int MiniSSC::actuate(int ch, int pos)
{
 char buffer[3];
 
 buffer[0] = 0xFF;
 buffer[1] = (char)(ch);
 if ( ch < 0 || ch > 7 )
  return -1;

 if (pos < 0x0) pos = 0x0;
 if (pos > 0xFE) pos = 0xFE;
 buffer[2] = (char)pos;

 if ( (write(d_serialPort, buffer, 3)) != 3 )
  return -1;

 return 0;
}
