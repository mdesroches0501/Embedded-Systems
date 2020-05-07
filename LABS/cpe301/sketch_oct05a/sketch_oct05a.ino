/*
volatile unsigned char* port_k = (unsigned char*) 0x108; 
volatile unsigned char* ddr_d  = (unsigned char*) 0x2A; 
volatile unsigned char* pin_b  = (unsigned char*) 0x23;
*/
volatile unsigned char* port_k = (unsigned char*) 0x108; 
volatile unsigned char* ddr_k  = (unsigned char*) 0x107; 
volatile unsigned char* pin_k  = (unsigned char*) 0x106;

volatile unsigned char* port_d = (unsigned char*) 0x2B; 
volatile unsigned char* ddr_d  = (unsigned char*) 0x2A; 
volatile unsigned char* pin_d  = (unsigned char*) 0x29;

volatile unsigned char* port_e = (unsigned char*) 0x2E; 
volatile unsigned char* ddr_e  = (unsigned char*) 0x2D; 
volatile unsigned char* pin_e  = (unsigned char*) 0x2C;

void setup() {

  Serial.begin(9600);
  //set PD0 to OUTPUT
  *ddr_k &= 0xFB;
  //*port_k |= 0x04;

  *ddr_d != 0x01;
  //*port_d |= 0x04;

  *ddr_e != 0x02;
  //*port_e |= 0x04;
 }

void loop() 
{
  
   // if the pin is high
  if(*pin_k &= 0x04)  //0b0000 0100
  {
    Serial.println("PIN IS HIGH");
    *port_d |= 0x01;
    *port_e &= 0xF7;
   
  }
 
  // if the pin is low
  else
  {
    Serial.println("PIN IS LOW");
    *port_d &= 0xFE;
    *port_e |= 0x08;
  }
  //delay(250);
  
}
