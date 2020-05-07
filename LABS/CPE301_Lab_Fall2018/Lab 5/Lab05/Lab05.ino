// Define Port B Register Pointers
volatile unsigned char* port_b = (unsigned char*) 0x25; 
volatile unsigned char* ddr_b  = (unsigned char*) 0x24; 
volatile unsigned char* pin_b  = (unsigned char*) 0x23; 

volatile unsigned char *myTCCR1A = (unsigned char *) 0x80;
volatile unsigned char *myTCCR1B = (unsigned char *) 0x81;
volatile unsigned char *myTCCR1C = (unsigned char *) 0x82;
volatile unsigned char *myTIMSK1 = (unsigned char *) 0x6F;
volatile unsigned int  *myTCNT1  = (unsigned  int *) 0x84;
volatile unsigned char *myTIFR1 =  (unsigned char *) 0x36;

  unsigned int freq;
 volatile unsigned int ticks = 0;

  char in_char;

  int myArray[12] = { 18181, 17167, 16194, 15296, 14440, 13628, 12820, 12139, 11461, 10810, 10200, 9626 }; //{440, 494, 523, 587, 659, 698, 784}; 
  //int mySharpArray[7] = {466, 0, 554, 624, 0, 740, 831};
  int myCharArray[12] = {'A', 'a', 'B', 'C', 'c', 'D', 'd', 'E', 'F', 'f', 'G', 'g'};

void setup() 
{

  
  // Initialize Timer1 for NORMAL mode, off, and no interrupts.
  *myTCCR1A = 0;
  *myTCCR1B = 0;
  *myTCCR1C = 0;
  *myTIMSK1 = 0;
  *myTCNT1 = 0;
  *ddr_b |= 0x40;
  //ticks = calc_ticks(440);

  Serial.begin(9600);
}

void loop() 
{
    // read in the character
  // if the UART received a character
  if(Serial.available())
  {
    // write the character back to the Serial Port
    
    in_char = Serial.read();
    Serial.write(in_char);
  }
  if (in_char != 'q')
    {
      ticks = myFunction(in_char);
    }else {
      ticks = 0;
      Serial.println(ticks);
    }

  if (ticks == 0){
        *port_b &= 0x00;
Serial.println(*port_b);
  }else {
    setFreq(ticks);
  }
    
}

   /* ticks = myFunction(in_char);
//    ticks =  freq; //calc_ticks(freq);
  }
    if (in_char == 'q')
    {
      *myTCCR1B &= 0xF8; // 0b111 
      setFreq(0);
    }

    if (in_char != 'q')
      setFreq(ticks);
}
*/
/*
unsigned int getFreq(unsigned char in_char)
{
   if(in_char > 'G')
  {
    return myArray[in_char - 'a'];
  }
  else
  {
    //If(in_char < 'C' && > 'A;)
    if (mySharpArray[in_char - 'A'] == 0)
      return freq; //in_char
    else
    {
      return mySharpArray[in_char - 'A'];
    }
  }
}
*/
unsigned int calc_ticks(double freq)
{  
  double period = 1 / freq;
  double squarewave = period / 2;
  double period_clck = .0000000625;
  double num_ticks = squarewave / period_clck;
  return num_ticks; 
}

void setFreq(double ticks)
{  
    *port_b |= 0x40;
    my_delay(ticks);
    *port_b &= 0xBF;
    my_delay(ticks);
}

void my_delay(double ticks)
{
  // stop the timer (set prescalar to 000)
  *myTCCR1B &= 0xF8; // 0b111 1000

  // set the counts (16 -> 2 addresses)
  *myTCNT1 = (unsigned int) (65536 - ticks);

  // start the timer (set prescalar to 001)
  *myTCCR1B |= 0x01; //0b000 0001

  // wait for overflow
  while((*myTIFR1 & 0x01) == 0); //0000 0001

  // stop the timer (set prescalar to 000)
  *myTCCR1B &= 0xF8; // 0b1111 1000

  // reset TOV (write a 1 to reset to 0)
  *myTIFR1 |= 0x01; // 0b0000
}

unsigned int myFunction(unsigned char in_char) {
  
  for(int i = 0; i < 12; i++) {
    if(myCharArray[i] == in_char)
    {
      return myArray[i];
    }
  }
}
