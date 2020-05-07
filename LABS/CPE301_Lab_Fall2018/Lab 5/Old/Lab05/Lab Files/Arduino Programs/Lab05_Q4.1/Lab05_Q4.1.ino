void MyDelay (unsigned long mSecondsApx );

void setup ()
{
unsigned char * portDDRB ;
portDDRB = (unsigned char *) 0x24 ;
* portDDRB |= 0x20 ; // Changed O's to 0's
}

void loop ()
{
unsigned char * portB ;
portB = (unsigned char *) 0x25 ;
* portB |= 0x20 ; // Changed O's to 0's
MyDelay (1000); // Changed curly brackets to parentheses ; Added a semicolon to the end of the line
* portB &= 0xDF ; // Changed O's to 0's; Changed colon to semicolon
MyDelay (1000); // Changed brackets to parentheses ; Added a semicolon to the end of the line
}

void MyDelay (unsigned long mSecondsApx )
{
volatile unsigned long i;
unsigned long endTime = 1000 * mSecondsApx ;
for (i = 0; i < endTime ; i ++) ;
}

