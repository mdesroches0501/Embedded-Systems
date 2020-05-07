// CPE 301: Lab 05, Question 3.1
// October 4th, 2017
// Created by Alexis Diaz

// initialize digital pin LED_BUILTIN as an output.
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

// Flashes the LED on and off, and every loop the flash goes faster
void loop() {
  for (int i = 1000; i -= 50; i > 0){
  digitalWrite(LED_BUILTIN, HIGH);    // turn the LED on (HIGH is the voltage level)
  delay(i);                           //wait
  digitalWrite(LED_BUILTIN, LOW);     // turn the LED off by making the voltage LOW
  delay(i/10);                        //wait
  }
}
