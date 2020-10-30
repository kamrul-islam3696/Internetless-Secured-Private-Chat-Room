// See VirtualWire.h for detailed API docs

#include <VirtualWire.h>
//byte addresses[][6] = {"0"};
char inData[60]; // Allocate some space for the stringi
char inChar; // Where to store the character read
byte index = 0; // Index into array; where to store the character
int val;
char msg[60];

void setup()
{
    Serial.begin(9600);	// Debugging only

    // Initialise the IO and ISR
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_set_rx_pin(8);
    vw_set_tx_pin(12);
    vw_setup(2000);	 // Bits per sec

    vw_rx_start();       // Start the receiver PLL running
}

void loop()
{
  
  while (Serial.available() > 0) //Get values from user
  {
    val = Serial.peek();
    if (index < 59) // One less than the size of the array
    {
      inChar = Serial.read(); // Read a character
      inData[index] = inChar; // Store it
      index++; // Increment where to write next
      inData[index] = '\0'; // Null terminate the string
    }
    if (val == '#')
    {
      strcpy( msg, inData);
      WriteData(); //Put module in Transmit mode
      while (index != 0)
      {
        inData[index] = ' ';
        index--;
      }
    }
  }
  ReadData(); //Put module Receive mode
}
void ReadData(){
  vw_rx_start(); 
   uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

   if (vw_get_message(buf, &buflen)) // Non-blocking
    {

        digitalWrite(13, true); // Flash a light to show received good message
  // Message with a good checksum received, dump it.  
  for (int i = 0; i < buflen; i++)
  {
      Serial.write(buf[i]);
  }
  Serial.println("");
        digitalWrite(13, false);
    }
}
void WriteData(){
    vw_rx_stop();       // Stop the receiver PLL running
    digitalWrite(13, true); // Flash a light to show transmitting
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false);
    delay(200);
}

