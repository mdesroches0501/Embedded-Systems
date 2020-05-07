#define RDA 0x80  
#define TBE 0x20  

volatile unsigned char* port_b = (unsigned char*) 0x25;
volatile unsigned char* ddr_b = (unsigned char*) 0x24;
volatile unsigned char* pin_b = (unsigned char*) 0x23;


volatile unsigned char *myUSART_CSR0A = (unsigned char *)0x00C0; /* Control -- Status */
volatile unsigned char *myUSART_CSR0B = (unsigned char *)0x00C1; /* Control -- Status */
volatile unsigned char *myUSART_CSR0C = (unsigned char *)0x00C2; /* Control -- Status */
volatile unsigned int  *myUSART_BRR0  = (unsigned int *) 0x00C4; /* Baud Rate (Lower/Upper) */
volatile unsigned char *myUSART_DR0   = (unsigned char *)0x00C6; /* Data */

volatile unsigned char *myTCCR1A = (unsigned char *) 0x80;
volatile unsigned char *myTCCR1B = (unsigned char *) 0x81;
volatile unsigned char *myTCCR1C = (unsigned char *) 0x82;
volatile unsigned char *myTIMSK1 = (unsigned char *) 0x6F;
volatile unsigned int  *myTCNT1  = (unsigned  int *) 0x84;
volatile unsigned char *myTIFR1 =  (unsigned char *) 0x36;


unsigned char regStatus;

/* UART FUNCTION PROTOTYPES: */
void USART_init(unsigned long baudVal);
unsigned char USART_kbhit();
unsigned char USART_getchar();
void USART_putchar(unsigned char charVal);


bool speakerState = false;

unsigned char input;

volatile int currentNote = 0;

/* To hold the proper currentNote-value, times are in milliseconds. */
unsigned long loadValue[13] = {18181, 17167, 16194, 15296, 14440, 13628, 12820, 12139, 11461, 10810, 10204, 9626, 0};

int myCharArray[13] = {'A', 'a', 'B', 'C', 'c', 'D', 'd', 'E', 'F', 'f', 'G', 'g', 'q'};

void setup()
{
  
  //Global flags
  SREG |= 0x80;
  
  USART_init(9600);

  //Timer init
  *myTCCR1A = 0;
  *myTCCR1B = 0;// Stops timer
  *myTCCR1C = 0;
  *myTIMSK1 |= 0x01; //starts timer

  //Pin 4 out
  *ddr_b |= 0x10;
   
  //start timer
  *myTCNT1 = (unsigned int) (65536 - currentNote);
   //USART_init(9600);
   *myTCCR1B |= 0x01;
}

/* Continuous processing occurs in the loop() function. */
void loop()
{
  //wait for input
  if (USART_kbhit())
  {
    //Take input
    input = USART_getchar();

    //save interupt status
    unsigned char regStatus = (unsigned char) SREG;
    
    SREG &= 0x7F;
    
    //*myTCCR1B |= 0x01;
    for(int i = 0; i < 13; i++)
    {
      if(myCharArray[i] == input)
      {
        *myTCCR1B |= 0x01;
        currentNote = loadValue[i];
      }
    }
 
    SREG = regStatus;
    USART_putchar(input);
  }
}

/* USE an interrupt service routine with Timer 1 
overflow flag bit as its only parameter.*/
ISR(TIMER1_OVF_vect)
{
  //USART_putchar('0');
  //Turn off timer 
  *myTCCR1B &= 0xF8;

  /* Load Timer/Counter 1. */
  *myTCNT1 = (unsigned int) (65536 - currentNote);

  /* If the sound is not playing, turn it on. */
  if(currentNote != 0)
  {
    if (!speakerState)
    {
      *port_b |= 0x40;
      speakerState = true;
    }
    else /* If the sound is playing, turn it off. */
    {
      *port_b = 0;//0xEF; //set this
      speakerState = false;
    }
  }
  else
  {
   *port_b = 0;//0xEF;
  }
 

  /* Set the precsaler to 1 (no-prescaling), Timer 1, NORMAL mode. */
  *myTCCR1B |= 0x01;
  
  //reset the timer
  //*myTIFR1 |= 0x01;
}

/* Initializes the USART's settings/modes. */
void USART_init(unsigned long baudVal)
{
  /* Holds the CPU frequency, and baud rate to store in UBRR. */
  unsigned long cpuFreq = 16000000; /* Assumes CPU frequency is 16 MHz. */
  unsigned int baudUBRR;            /* Stores the baud rate. */

  /* Calculate the UBRR value. */
  baudUBRR = (((unsigned long) (cpuFreq / ((unsigned long) (16 * baudVal)))) - 1);

  *myUSART_CSR0A = 0x20;    /* Sets the UDRE bit and FE bit, disables MPCM. */
  *myUSART_CSR0B = 0x18;    /* Turns on RXEN and TXEN, turns off all interrupts. */
  *myUSART_CSR0C = 0x06;    /* Sets 8-bit character size, turns off parity, uses 1 stop bit. */
  *myUSART_BRR0 = baudUBRR; /* Loads the USART Baud Rate Register -- UBRR0. */
}

/* Reads the RDA status bit and returns non-zero...(true) if set. */
unsigned char USART_kbhit()
{
  volatile unsigned char getStatus;   /* Holds the RDA status bit. */
  getStatus = (*myUSART_CSR0A & RDA); /* Determines if there is data available to read. */
  return getStatus;                   /* Returns the RDA status bit. */
}

/* Reads the input character from USART's input-buffer */
unsigned char USART_getchar()
{
  volatile unsigned char inputChar;  /* Holds the character passed to the USART Data Buffer Register. */
  inputChar = *myUSART_DR0;          /* Stores the value held in the USART Data Buffer Register to inputChar. */
  return inputChar;                  /* Returns the value assigned to inputChar from the USART Data Buffer Register. */
}

/* Waits for USART TBE to be set then writes character to transmit buffer. */
void USART_putchar(unsigned char charVal)
{
  while ((*myUSART_CSR0A & TBE) == 0); /* Wait until the Transmit Complete flag bit is set and the transmitter is ready. */
  *myUSART_DR0 = charVal;              /* Update the USART Data Buffer Register by writing new data to the register. */
}
