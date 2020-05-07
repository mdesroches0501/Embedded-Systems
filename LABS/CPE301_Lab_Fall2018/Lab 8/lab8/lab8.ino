// defining global variables 
volatile unsigned char *my_ADCSRA = (unsigned char*) 0x7A;
volatile unsigned char *my_ADCSRB = (unsigned char*) 0x7B;
volatile unsigned char *my_ADMUX = (unsigned char*) 0x7C;
volatile unsigned int *my_ADLAR = (unsigned int*) 0x78;

#define RDA 0x80
#define TBE 0x20  
volatile unsigned char *myUCSR0A = (unsigned char *)0x00C0;
volatile unsigned char *myUCSR0B = (unsigned char *)0x00C1;
volatile unsigned char *myUCSR0C = (unsigned char *)0x00C2;
volatile unsigned int  *myUBRR0  = (unsigned int *) 0x00C4;
volatile unsigned char *myUDR0   = (unsigned char *)0x00C6;

void setup()
{
 // initialize the serial port on USART0:
 U0init(9600);

 // converts analog signal to digital
 adc_init();
}

void loop()
{
  int number;
  int first;
  int second;
  int third;
  int fourth;

  
  number = adc_read(10);
  fourth = (number % 10) + 48;
  number /= 10;
  third = (number % 10) + 48;
  number /= 10;
  second = (number % 10) + 48;
  number /= 10;
  first = (number % 10) + 48; 

  U0putchar(first);
  U0putchar(second);
  U0putchar(third);
  U0putchar(fourth);
  U0putchar('\n');
  
} 

//
// Read input character from USART0 input buffer
//
unsigned char U0getchar()
{
return (*myUDR0);
}


//
// Wait for USART0 TBE to be set then write character to
// transmit buffer
//
void U0putchar(unsigned char U0pdata)
{
  while ((*myUCSR0A & TBE) == 0){} 
  *myUDR0 = U0pdata;
}

void U0init(unsigned long U0baud)
{
//  Students are responsible for understanding
//  this initialization code for the ATmega2560 USART0
//  and will be expected to be able to intialize
//  the USART in differrent modes.
//
 unsigned long FCPU = 16000000;
 unsigned int tbaud;
 tbaud = (FCPU / 16 / U0baud - 1);
 // Same as (FCPU / (16 * U0baud)) - 1;
 *myUCSR0A = 0x20;
 *myUCSR0B = 0x18;
 *myUCSR0C = 0x06;
 *myUBRR0  = tbaud;
}

void adc_init( ){
  *my_ADMUX = 0x40; 
  *my_ADCSRA = 0x80;
  *my_ADCSRB &= 0xF8;
}

unsigned int adc_read(unsigned char adc_channel){

  if(adc_channel > 7)
  {
    *my_ADCSRB |= 0b00001000;
  }
  else
  {
    *my_ADCSRB &= 0b11110111;
  }

  adc_channel = adc_channel % 8;
  *my_ADMUX &= 0b11100000;
  *my_ADMUX += adc_channel;
  
  *my_ADCSRA |= 0x40;
  while(*my_ADCSRA & 0x40){}
  return *my_ADLAR; 
}
