
// get a pointer to the EEPROM ADDRESS REGISTER (16-bit)
volatile unsigned int* EEPROM_ADDR_REG = (unsigned int*) 0x41;
// get a pointer to the EEPROM Data Register (8-bit)
volatile unsigned char* EEPROM_DATA_REG = (unsigned char*) 0x40;
// get a pointer to the EEPROM Control Register (8-bit)
volatile unsigned char* EEPROM_CNTRL_REG = (unsigned char*) 0x3F;

// Define Port B Register Pointers
volatile unsigned char *port_b = (unsigned char*) 0x25;
volatile unsigned char *ddr_b = (unsigned char*) 0x24;
volatile unsigned char *pin_b = (unsigned char*) 0x23;

volatile unsigned char *port_f = (unsigned char*) 0x108;
volatile unsigned char *ddr_f = (unsigned char*) 0x107;
volatile unsigned char *pin_f = (unsigned char*) 0x106;



unsigned char bitcnt = 0;
unsigned int address = 0x0025;

unsigned int numbers[16] = {0b0111000, 0b0000010, 0b1001111, 0b0010001, 0b0000101, 0b1001100, 0b0100100, 0b0100000, 0b0001111, 0b0000000, 0b0001100, 0b0001000, 0b1100000, 0b0110010, 0b1000001, 0b0110000};//, 0b0111000};

void setup() {
  // Start Serial
  Serial.begin(9600);

   *ddr_f = 0xFF;

   //set PB4 to INPUT
   *ddr_b &= 0xEF;
   // enable the pullup resistor on PB4
   *port_b |= 0x10; 
 
  bitcnt = eeprom_read(address);  // Read the data back from the address we picked
  *port_f = numbers[bitcnt];
}

void loop()
{
  if(!(*pin_b & 0x10))
  {
    delay(20);
    if(!(*pin_b & 0x10))
    { 
      Serial.println(bitcnt);
      bitcnt++;
      if(bitcnt > 15)
      {
        bitcnt = 0;
      }
     
        *port_f = numbers[bitcnt];
        eeprom_write(address, bitcnt);
        while(!(*pin_b & 0x10));
      }
    }
   
}


void eeprom_write(unsigned int address, unsigned char data_in)
{
  /* Wait for completion of previous write */
  while(*EEPROM_CNTRL_REG & 0x02);
  /* Set up address and Data Registers */
  *EEPROM_ADDR_REG = address;
  *EEPROM_DATA_REG = data_in;
  /* Write logical one to EEMPE */
  *EEPROM_CNTRL_REG |= 0x04;
  /* Write logical zero to EEPE */
  *EEPROM_CNTRL_REG &= ~(0x02);
  /* Write logical one to EEPE */
  *EEPROM_CNTRL_REG |= 0x02;
}
unsigned char eeprom_read(unsigned int address)
{
  /* Wait for completion of previous write */
  while(*EEPROM_CNTRL_REG & 0x02);
  /* Set up address register */
  *EEPROM_ADDR_REG = address;
  /* Start eeprom read by writing EERE */
  *EEPROM_CNTRL_REG |= 0x01;
  /* Return data from Data Register */
  return *EEPROM_DATA_REG;
}
