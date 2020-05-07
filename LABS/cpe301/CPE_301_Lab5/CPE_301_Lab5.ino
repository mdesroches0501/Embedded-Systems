// Define Port B Register Pointers
volatile unsigned char* port_b = (unsigned char*) 0x25; 
volatile unsigned char* ddr_b  = (unsigned char*) 0x24; 
volatile unsigned char* pin_b  = (unsigned char*) 0x23; 

// Initalizing the Timer/counter port for delay 
volatile unsigned char* my_TCCR1A = (unsigned char*) 0x80;
volatile unsigned char* my_TCCR1B = (unsigned char*) 0x81;
volatile unsigned char* my_TCCR1C = (unsigned char*) 0x82;

// Initializes the interupt flag register
volatile unsigned char* my_TIFR1 = (unsigned char*) 0x36;

// Need this to acces the Timer/counter value
volatile unsigned int* my_TCNT1 = (unsigned int*) 0x84;

// initialize out Timer interrupt mask register
volatile unsigned char* my_TIMSK1 = (unsigned char*) 0x6F;

// make interger for out ticks
unsigned int ticks;

void setup() {
  // put your setup code here, to run once:

  // set timer pointers to 0 
  *my_TCCR1A = 0;
  *my_TCCR1B = 0;
  *my_TCCR1C = 0;

  //set counter value to 0
  *my_TCNT1 = 0;

  //set mask to 0
  *my_TIMSK1 = 0;

  // UART from example
  // setup the UART
  Serial.begin(9600);

  // mask ddr_b
  *ddr_b |= 0x40;

}

void loop() {
  // put your main code here, to run repeatedly:

  double frequency;
  //frequency = 0;

  // if the UART received a character
  if(Serial.available())
  {
    // read in the character
    unsigned char in_char = Serial.read();
    // write the character back to the Serial Port
    Serial.write(in_char);


   
    
    switch(in_char)
    {

      case 'a':
      {
        frequency = 440;
        ticks = find_ticks(frequency);
        Serial.write('\n');
        break;       
      }
      case 'A':
      {
        frequency = 466;
        ticks = find_ticks(frequency);
        Serial.write('\n');
        break;       
      }
      case 'b':
      {
        frequency = 494;
        ticks = find_ticks(frequency);
        Serial.write('\n');
        break; 
      }
      case 'c':
       {
        frequency = 523;
        ticks = find_ticks(frequency);
        Serial.write('\n');
        break; 
      }
      case 'C':
      {
        frequency = 554;
        ticks = find_ticks(frequency);
        Serial.write('\n');
        break; 
      }
      case 'd':
      {
        frequency = 587;
        ticks = find_ticks(frequency);
        Serial.write('\n');
        break; 
      }
      case 'D':
      {
        frequency = 624;
        ticks = find_ticks(frequency);
        Serial.write('\n');
        break; 
      }
      case 'e':
      {
        frequency = 659;
        ticks = find_ticks(frequency);
        Serial.write('\n');
        break; 
      }
      case 'f':
      {
        frequency = 698;
        ticks = find_ticks(frequency);
        Serial.write('\n');
        break; 
      }
      case 'F':
      {
        frequency = 740;
        ticks = find_ticks(frequency);
        Serial.write('\n');
        break; 
      }
      case 'g':
      {
        frequency = 784;
        ticks = find_ticks(frequency);
        Serial.write('\n');
        break; 
      }
      case 'G':
      {
        frequency = 831;
        ticks = find_ticks(frequency);
        Serial.write('\n');
        break; 
      }
      case 'q':
      {
        frequency = 0;
        ticks = find_ticks(frequency);
       
        Serial.write('\n');
        break; 
      }
      default:
      {
        Serial.write(" Enter a valid letter!");
        break;
      }
    }

  }

  if(ticks != 0){
  *port_b |= 0x40;
  my_delay(ticks);
  *port_b &= 0xBF;
  my_delay(ticks);
  }
  else 
  return 0;

}

double find_ticks(double frequency){
if(frequency == 0)
return 0;

  double period_clock = .0000000625; // equals (1/(1.6*10^7))

  double period;
  period = (1/frequency);

  double square_wave;
  square_wave = (period/2);

  double ticks_num = (square_wave/period_clock);

  return ticks_num;  
}

//delay func from class
void my_delay(unsigned int ticks){
  
  // stop the timer (set prescaler to 000)
  *my_TCCR1B &= 0xF8;
  // set the counts (16 bits -> 2 addresses!)
  *my_TCNT1 |= (unsigned int) (65536- ticks);
  //start the timer (set prescaler to 001)
  *my_TCCR1B |= 0x01; 
  //wait for overflow
  while((*my_TIFR1 & 0x01) == 0);
  //stop the timer (set prescaler to 000)
  *my_TCCR1B &= 0xF8;
  // reset TOV (write a 1 to reset 0)
  *my_TIFR1 |= 0x01; 
   
}
