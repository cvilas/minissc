REAME file for MiniSSC library version 1.0
Author: Vilas K Chitrakaran

Introduction
============

The Mini Serial Servo Controller (SSC) is a simple device that can be used to 
control upto eight pulse-proportional servos. These servos are designed for 
use in toys such as radio-controlled (R/C) cars. They are fast and surprisingly
powerful, making them suitable also for applications such as pan-tilt cameras 
and small robotic arms. The shaft position of the servos are controlled by 1ms 
to 2ms wide pulses repeating at 60Hz frequency. The Mini SSC II has an on-board 
PIC controller that accepts control words received serially at 2400 or 9600 
baud, and generates the necessary control signals for the 8 servos.

    * There is a nice overview of the working of servos here: 
	http://www.seattlerobotics.org/guide/servohack.html.
    * You can get the data sheets and the user's manual for the MiniSSC II 
      from Scott Edwards Electronics Incorporated: 
        http://www.seetron.com/ssc.htm
    * Medonis Engineering makes a nice Battery booster to eliminate the dual
      power supply requirement of the MiniSSC board:
        http://www.medonis.com/booster12.html
    * A good guide to serial port programming in POSIX systems is here:
        http://www.easysw.com/~mike/serial/

MiniSSC II is a simple device and all you need to know is how to set the output 
baud rate of the serial port. In order to control servos connected to a Mini SSC, 
the controller software has to send three bytes at the appropriate serial rate 
continuously. These three bytes are

    * Byte 1: sync marker (255)
    * Byte 2: servo number (0-254)
    * Byte 3: servo position(0-254) 

The class library libMiniSSC provides the bare minimum functionality required to 
control a Mini SSC II. This is all you need if you need a low level interface to 
directly control the servos.


Installation
============

To compile and install, please use the makefile provided in the package. Do the 
following

   1. Unzip and untar the package into a temporary directory.

      cd /tmp
      tar zxvf MiniSSC.tgz

   2. Enter the top directory and inspect the makefile. The installation
      directories are set by varaibles in the makefile and the defaults
      are as follows:
      
      Header files: /usr/local/inlcude/MiniSSC
      Library: /usr/local/lib

      You may change these to another directory by editing the corresponding 
      variables in the makefile. After that, install the library as follows,
      
      make
      make install

      These commands will make the shared and static libraries libMiniSSC.so 
      and libMiniSSC.a respectively, and install them in the location specified 
      in the Makefile. 
      
   3. Try the provided example program MiniSSC.t.cpp.

Applications
============

I wrote this software primarily to control my Lynxmotion 5 axis robot arm in 
Linux. The Mini SSC II is quite popular with hobbyists, and is used in a lot 
of other devices. Have a look at http://www.seetron.com/ssclinks.htm for more 
Mini SSC II applications.

Suggestions or comments? Mail me at cvilas@ces.clemson.edu

