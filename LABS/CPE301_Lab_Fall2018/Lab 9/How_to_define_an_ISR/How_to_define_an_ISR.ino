/*  
 *  How to define an ISR example
 *  This is an empty example demonstrating how 
 *  an ISR is defined.
 */


void setup() 
{                
  /* 
   *  The TIMER 1 OVERFLOW interrupt
   *  must be enabled here
   */
}

void loop() 
{
  /* 
   *  This is the normal loop function. This code may be
   *  interrupted by the ISR when the interrupt occurs.
   */
}
// TIMER OVERFLOW ISR
ISR(TIMER1_OVF_vect)
{
  /*  
   *   This function(AKA ISR) 
   *  will run whenever TIMER 1 
   *  overflows (whenever TOV is set)
   */
}


