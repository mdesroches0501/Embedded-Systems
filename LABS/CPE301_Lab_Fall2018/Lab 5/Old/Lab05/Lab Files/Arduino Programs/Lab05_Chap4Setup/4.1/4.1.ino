# define DEBUG_OUTPUT_MESSAGE_MAX_LENGTH 80
void setup ()
{
char message [ DEBUG_OUTPUT_MESSAGE_MAX_LENGTH ];
snprintf ( message , DEBUG_OUTPUT_MESSAGE_MAX_LENGTH , "Hello ,World !\n");

Serial.begin(9600);
Serial.write(message);  
}
void loop ()
{}
