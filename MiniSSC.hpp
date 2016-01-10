//==============================================================================
// MiniSSC.hpp - MiniSSC II Communication Module
//
// Author        : Vilas Kumar Chitrakaran
// Version       : 1.0 (April 2002) - first version, 
//                 2.0 (May 2005) - some enhancements.
// Compatibility : POSIX, GCC
//==============================================================================

#ifndef _INCLUDED_MINISSC_HPP
#define _INCLUDED_MINISSC_HPP

#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

//==============================================================================
// class MiniSSC
// -----------------------------------------------------------------------------
// \brief
// Functions required to communicate with a Mini SSC II controller from
// Scott Edwards Electronics, Inc. 
//
// The MiniSSC II is a simple pulse proportional servo controller for upto 
// eight servos. The jumpers used to configure the controller are as follows :
// <ul>
// <li> R (range)    : OFF - 90 degrees, ON - 180 degrees.
// <li> I (servo id) : OFF - 0 to 7, ON - 8 to 15.
// <li> B (baud)     : OFF - 2400, ON - 9600.
// </ul>
// The above jumper settings are not readable via software and hence must be
// correctly specified to the software by the user. For more details about the
// controller, see http://www.seetron.com/ssc.htm
// 
// <b>Example Program:</b>
// \include MiniSSC.t.cpp
//==============================================================================

class MiniSSC 
{
 public:    
  MiniSSC();  
   // The constructor does nothing important.            
  
  ~MiniSSC();
   // The destructor cleans up.

  int reset(const char *portName, bool ij, bool bj);
   // Sets up the serial port and resets all servos to zero.
   //  portName  Serial port name (eg: /dev/ttyS0)
   //  ij        Set this to true if 'I' jumper is set, else false.
   //  bj        Set this to true if 'B' jumper is set, else false.
   //  return    0 on success, else -1.
   // <br><hr>
   // Note: See MiniSSC manual for jumper settings.
   // <br><hr>
  
 int actuate(int channel, int pos);
   // Drive an output channel to the desired position.
   // The range of rotation (90 or 180 deg.) of the motor 
   // will depend on the jumper setting 'R'.
   //  channel output channel [0 - 7].
   //  pos     desired position [0 - 254].
   //  return  0 on success, else -1.

  // ========== END OF INTERFACE ==========

 private: 
  int d_serialPort;
};


#endif // _INCLUDED_MINISSC_HPP
