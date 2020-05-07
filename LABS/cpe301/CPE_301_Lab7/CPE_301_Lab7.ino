/*
 *  CPE 301 - EEPROM Reading and Writing Example
 *  For details see Atmel 2560 Datasheet Page 30, 35
 *  Written by Frank Mascarich, Spring 2018
 */
// get a pointer to the EEPROM ADDRESS REGISTER (16-bit)
volatile unsigned int* EEPROM_ADDR_REG = (unsigned int*) 0x41;
// get a pointer to the EEPROM Data Register (8-bit)
volatile unsigned char* EEPROM_DATA_REG = (unsigned char*) 0x40;
// get a pointer to the EEPROM Control Register (8-bit)
volatile unsigned char* EEPROM_CNTRL_REG = (unsigned char*) 0x3F;

//define port b
volatile unsigned char *port_b = (unsigned char*) 0x25;
volatile unsigned char *ddr_b = (unsigned char*) 0x24;
volatile unsigned char *pin_b = (unsigned char*) 0x23;
//define port f

volatile unsigned char *port_f = (unsigned char*) 0x31;
volatile unsigned char *ddr_f = (unsigned char*) 0x30;
volatile unsigned char *pin_f = (unsigned char*) 0x2F;

/*
volatile unsigned char *port_f = (unsigned char*) 0x108;
volatile unsigned char *ddr_f = (unsigned char*) 0x107;
volatile unsigned char *pin_f = (unsigned char*) 0x106;
*/
//Set the bit count
unsigned char bitcnt = 0;

//set the address
unsigned int address = 0x0025;

//set the array of numbers
//unsigned int numbers[16] = {0x01, 0x4F, 0x12, 0x06, 0x4C, 0x24, 0x20, 0x0F, 0x00, 0x0C, 0x08, 0x00, 0x31, 0x01, 0x30, 0x38};      
//unsigned int numbers[16] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111, 0b01110111, 0b01111111, 0b00111001, 0b00111111, 0b01111001, 0b01110001};
  unsigned int numbers[16] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10011000, 0b10001000, 0b10000011, 0b11000110, 0b10100001, 0b10000110, 0b10001110};
void setup() {
  // Start Serial
  Serial.begin(9600);
  /*
  unsigned char data_in = 0x41;     // Make up some data to save
  unsigned char data_out = 0x00;    // Create a variable to read it back fom
  unsigned int address = 0x0025;    // Pick a random address to save it
  eeprom_write(address, data_in);   // Save the data input to the address we picked
  data_out = eeprom_read(address);  // Read the data back from the address we picked-
  if(data_in != data_out)           // Check to make sure what we wrote is what we read
  {
    Serial.println("EEPROM Error");
  }
  Serial.print("Data input : ");    // Print the data back to the serial terminal
  Serial.print(data_in, HEX);
  Serial.print(", Data output : " );
  Serial.println(data_out, HEX);
  */
   //set to output
   *ddr_f = 0xFF;
   //PB4 = INPUT
   *ddr_b &= 0xEF;
   // enable the pullup resistor on PB4
   *port_b |= 0x10; 

    // Read from the address
    bitcnt = eeprom_read(address);
    
    *port_f = numbers[bitcnt];
    //while(1);
}
void loop() 
{
  
  if(!(*pin_b & 0x10))
  {
    delay(2);
    
    if(!(*pin_b & 0x10))
    { 
      Serial.println(bitcnt);
      //increase bit count
      
      
      
      if(bitcnt > 15)
        bitcnt = 0;
      
      *port_f = numbers[bitcnt];
      eeprom_write(address, bitcnt);

    bitcnt++;
          if(bitcnt > 15)
        bitcnt = 0;
      
      //wait while pin b is ready
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

