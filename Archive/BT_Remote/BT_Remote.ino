
// Basic Bluetooth sketch HC-05_AT_MODE_01
// Connect the HC-05 module and communicate using the serial monitor
//
 
#include <SoftwareSerial.h>

//creates an object to control the BT connection
SoftwareSerial BT(2, 3); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.

///////////////
//BUTTON PINS//
///////////////

#define LEFT_UP       4
#define LEFT_DOWN     5
#define LEFT_SETBACK  A2
#define RIGHT_UP      A5
#define RIGHT_DOWN    9
#define RIGHT_SETBACK A4

//character variable for use in communicating information between boards**
char c = ' ';

bool ignoreSetback = false;

void setup() 
{
    Serial.begin(9600);
    Serial.println("Arduino is ready");
    Serial.println("Remember to select Both NL & CR in the serial monitor");
    BT.begin(9600); //change to match your BT module
    pinMode(LED_BUILTIN, OUTPUT);

    //master pins
    pinMode(LEFT_UP, INPUT);
    pinMode(LEFT_DOWN, INPUT);
    pinMode(LEFT_SETBACK, INPUT);
    pinMode(RIGHT_UP, INPUT);
    pinMode(RIGHT_DOWN, INPUT);
    pinMode(RIGHT_SETBACK, INPUT);
}
 
void loop()
{ 
  //Pretty sure all of this only needs to be on master
  if (digitalRead(LEFT_SETBACK) == HIGH && digitalRead(RIGHT_SETBACK) == HIGH)
  {
    c = 'U';
    Serial.println("Reset");
    BT.write(c);
    ignoreSetback = true;
    delay(1000);
  }
  
  if (digitalRead(LEFT_UP) == HIGH) 
  {
    c = 'Q';
    Serial.println("Button Press LEFT_UP"); //feedback that button is working
    BT.write(c); //sends variable to other board via Bluetooth
    delay(200);
  }

  if (digitalRead(LEFT_DOWN) == HIGH)
  {
    c = 'W';
    Serial.println("Button Press LEFT_DOWN"); //feedback that button is working
    BT.write(c); //sends variable to other board via Bluetooth
    delay(200);
  }

  if (digitalRead(LEFT_SETBACK) == HIGH && !ignoreSetback)
  {
    c = 'E';
    Serial.println("Button Press LEFT_SETBACK");
    BT.write(c);
    delay(200);
  }

  if (digitalRead(RIGHT_UP) == HIGH)
  {
    c = 'R';
    Serial.println("Button Press RIGHT_UP");
    BT.write(c);
    delay(200);
  }

  if (digitalRead(RIGHT_DOWN) == HIGH)
  {
    c = 'T';
    Serial.println("Button Press RIGHT_DOWN");
    BT.write(c);
    delay(200);
  }

  if (digitalRead(RIGHT_SETBACK) == HIGH && !ignoreSetback)
  {
    c = 'Y';
    Serial.println("Button Press RIGHT_SETBACK");
    BT.write(c);
    delay(200);
  }

  ignoreSetback = false;
 
}
