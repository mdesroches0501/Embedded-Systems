void NewDelay (unsigned char mSecondsApx );
void setup ()
{
unsigned char * portDDRB ;
*portDDRB = (unsigned char *) 0x24 ;
* portDDRB |= 0x80 ;
}
void loop ()
{
unsigned char * portB ;
*portB = (unsigned char *) 0x25 ;
* portB |= 0x20 ;
NewDelay (100) ;
* portB &= 0x7F ;
NewDelay (100) ;
}

void NewDelay (unsigned char mSecondsApx )
{
volatile unsigned char i;
unsigned long endTime = 1000 * mSecondsApx ;
for (i = 0; i < endTime ; i ++) ;
}
