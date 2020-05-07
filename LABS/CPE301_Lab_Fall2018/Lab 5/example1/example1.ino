// Serial Echo Example

    unsigned int tix;
volatile unsigned char* port_b = (unsigned char*) 0x25;
volatile unsigned char* ddr_b = (unsigned char*) 0x24;
volatile unsigned char* pin_b = (unsigned char*) 0x23;

volatile unsigned char* myTCCR1A = (unsigned char*) 0x80;
volatile unsigned char* myTCCR1B = (unsigned char*) 0x81;
volatile unsigned char* myTCCR1C = (unsigned char*) 0x82;
volatile unsigned char* myTIFR1 = (unsigned char*) 0x36;
volatile unsigned int* myTCNT1 = (unsigned int*) 0x84;
volatile unsigned char* myTIMSK1 = (unsigned char*) 0x6F;

void setup() 
{
  *myTCCR1A = 0;
  *myTCCR1B = 0;
  *myTCCR1C = 0;

  *myTIMSK1 = 0;
  *myTCNT1 = 0;
  // setup the UART
  Serial.begin(9600);
  *ddr_b |= 0x40;
  
}
void loop() 
{
  unsigned int freq = 0;
  unsigned char in_char;
  // if the UART received a character
  if(Serial.available())
  {
    // read in the character
    in_char = Serial.read();
    // write the character back to the Serial Port
    Serial.write(in_char);
    
  
    

    switch(in_char){
    case 'a':
      freq = 440;
      tix = calc_ticks(freq);
      break;
    case 'A':
      freq = 466;
      tix = calc_ticks(freq);
      break;
    case 'b':
      freq = 494;
      tix = calc_ticks(freq);
      break;
    case 'c':
      freq = 523;
      tix = calc_ticks(freq);
      break;
    case 'C':
      freq = 554;
      tix = calc_ticks(freq);
      break;
    case 'd':
      freq = 587;
      tix = calc_ticks(freq);
      break;
    case 'D':
      freq = 624;
      tix = calc_ticks(freq);
      break;
    case 'e':
      freq = 659;
      tix = calc_ticks(freq);
      break;
    case 'f':
      freq = 698;
      tix = calc_ticks(freq);
      break;
    case 'F':
      freq = 740;
      tix = calc_ticks(freq);
      break;
    case 'g':
      freq = 784;
      tix = calc_ticks(freq);
      break;
    case 'G':
      freq = 831;
      tix = calc_ticks(freq);
      break;
    
    case 'q':
      //freq = 0;
      //tix = calc_ticks(freq);
        *myTCCR1B &= 0xF8;
      break;
    
    default:

      break;
  }
  }
  
  *port_b |= 0x40;
  my_delay(tix);
  *port_b &= 0xBF;
  my_delay(tix);
  
}


void my_delay(unsigned int ticks){
  // stop the timer (set prescaler to 000)
  *myTCCR1B &= 0xF8;
  // set the counts (16 bits -> 2 addresses!)
  *myTCNT1 |= (unsigned int) (65536- ticks);
  //start the timer (set prescaler to 001)
  *myTCCR1B |= 0x01; 
  //wait for overflow
  while((*myTIFR1 & 0x01) == 0);
  //stop the timer (set prescaler to 000)
  *myTCCR1B &= 0xF8;
  // reset TOV (write a 1 to reset 0)
  *myTIFR1 |= 0x01; 
  
}
double calc_ticks(double freq){
  
  double period = 1 / freq;
  double squarewave = period / 2;
  double period_clck = .0000000625;
  double num_ticks = squarewave / period_clck;
  return num_ticks; 
  
}
