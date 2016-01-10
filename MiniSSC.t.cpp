//==============================================================================
// MiniSSC.t.cpp - MiniSSC II Communication Module example
//
// Author        : Vilas Kumar Chitrakaran
//==============================================================================

#include "MiniSSC.hpp"
#include <math.h>
#include <time.h>

int main()
{
 MiniSSC port;
 if( port.reset("/dev/ttyUSB0", 0, 1) == -1)
 {
  fprintf(stderr, "reset failed\n");
  return -1;
 }
 
 int servoId = 0;
 int servoPos = 0;
 double t = 0;
 struct timespec napTime;
 napTime.tv_sec = 0;
 napTime.tv_nsec = (long int)1e6;
 
 while(1)
 {
  servoPos = (int)(120*( 1 + sin(t)));
  if( port.actuate(servoId%7, servoPos) == -1)
  {
   fprintf(stderr, "actuate failed\n");
   break;
  }
  t += 0.001;
  servoId++;
  nanosleep(&napTime, NULL);
 }
 return 0;
}
