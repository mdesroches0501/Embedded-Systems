// Define Port K Register Pointers
volatile unsigned char* port_k = (unsigned char*) 0x108;
volatile unsigned char* ddr_k = (unsigned char*) 0x107;
volatile unsigned char* pin_k = (unsigned char*) 0x106;

// Define Port D Register Pointers
volatile unsigned char* port_d = (unsigned char*) 0x2B;
volatile unsigned char* ddr_d = (unsigned char*) 0x2A;
volatile unsigned char* pin_d = (unsigned char*) 0x29;

// Define Port E Register Pointers
volatile unsigned char* port_e = (unsigned char*) 0x2E;
volatile unsigned char* ddr_e = (unsigned char*) 0x2D;
volatile unsigned char* pin_e = (unsigned char*) 0x2C;

void setup()
{
  Serial.begin(9600);
  
  // Set PK2 to input
  *ddr_k &= 0xFB; // 0b11111011
  *port_k &= 0x04; // 0b00000100
  
  // Set PD0 to output
  *ddr_d |= 0x01; // 0b00000001
  
  // Set PE3 to output
  *ddr_e |= 0x08; // 0b00001000
}

void loop()
{
  // the pin is high
  if(*pin_k & 0x04) // 0b00000100
  {
    Serial.println("PIN IS HIGH");
    *port_d |= 0x01; // 0b00000001
    *port_e &= 0xF7; // 0b11110111
  }
  
  // else the pin is low
  else
  {
    Serial.println("PIN IS LOW");
    *port_d &= 0xFE; // 0b11111110
    *port_e |= 0x08; //0b00001000
  }
  
  //delay(250);
}
