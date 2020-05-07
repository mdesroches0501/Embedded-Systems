// CPE 301: Lab 04
// Used in Questions 3 and 4
// September 27, 2017

int ledPin = 53;

// Initialize pins as outputs.
void setup()
{
  pinMode(ledPin, OUTPUT);
}

// Loops: Turns LED on, waits, Turns LED off, waits
void loop()
{
  // Change delay for faster blinking
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}

