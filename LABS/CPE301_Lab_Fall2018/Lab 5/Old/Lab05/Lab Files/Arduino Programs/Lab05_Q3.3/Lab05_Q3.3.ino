// CPE 301: Lab 05, Question 3.3
// October 4th, 2017
// Edited by Alexis Diaz

// Program to Blink Arduino Mega LED
// using timer for MyDelay.
//
//Written by D. Egbert, Version 1.4, 11/05/2015
//
// Cleaned up version of BlinkT
//
// Hardware pointers should be initialized Global variables
//
volatile unsigned char *myTCCR1A = (unsigned char *) 0x80;
volatile unsigned char *myTCCR1B = (unsigned char *) 0x81;
volatile unsigned char *myTCCR1C = (unsigned char *) 0x82;
volatile unsigned char *myTIMSK1 = (unsigned char *) 0x6F;
volatile unsigned int  *myTCNT1  = (unsigned  int *) 0x84;
volatile unsigned char *myTIFR1 =  (unsigned char *) 0x36;
volatile unsigned char *portDDRB = (unsigned char *) 0x24;
volatile unsigned char *portB =    (unsigned char *) 0x25;

void MyDelay(unsigned long mSeconds);

void setup ()
{
// Initialize Timer1 for NORMAL mode, off, and no interrupts.
*myTCCR1A = 0;
*myTCCR1B = 0;
*myTCCR1C = 0;
*myTIMSK1 = 0;
// Initialize GPIO PortB
*portDDRB |= 0x80;
}
// Flashes the LED on and off, and every loop the flash goes faster
void loop ()
{
  for (int i = 1000; i -= 50; i > 0)
  {
    *portB |= 0x80;
    MyDelay (i);
    *portB &= 0x7F;
    MyDelay (i/10);
  }
}

void MyDelay(unsigned long mSeconds)
{
//
// We want to delay for milliseconds (mSeconds) so we want to set up
// the timer for enough timer ticks to last mSeconds milliseconds.
// The Arduino Mega runs at F_CPU = 16 MHz so (with no prescaler)
// one timer tick = 1/(16 * 10^6) = 0.0625 microseconds (too fast). 
// With a prescaler of F_CPU/1024 one timer tick = 1024 clock periods, 
// which = 0.0625 * 10^-6 * 1024 = 0.064 milliseconds. 
// Thus, there are 1/0.064 timer ticks per second or 1/64 timer ticks per millisecond.
// dividing out gives us 15,625 ticks per second and 15.625 ticks per millisecond.
// This means we can load the timer with 65,536 - (15.625 * mSeconds).
//
*myTCCR1B &= 0xF8;              // make sure timer is off
*myTCNT1 = (unsigned int) (65536 - (long) (15.625 * mSeconds));
*myTCCR1B |= 0b00000101;        // Pre-scalar 1024, turn timer on (|=0x05)
while((*myTIFR1 & 0x01)==0);    // Wait for TIFR overflow flag bit to be set  
*myTCCR1B &= 0xF8;              // Turn off the timer after getting delay                          
*myTIFR1 |= 0x01;               // Clear the flag bit for next use
// NOTE: writing a 1 sets bit to 0 (don't ask)
}
  
