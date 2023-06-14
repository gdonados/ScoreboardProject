/*HC05 BT module uses 3.3V on board, GND to GND, Rx of HC05 to Tx of Arduino,
 * Tx of HC05 to Rx of Arduino, use a 2k, 1k voltage divider for Rx pin HC05
 * 
 */

#include <SoftwareSerial.h> //Library for BT module
SoftwareSerial BT(2,3); //RX||TX, May need to hook to pins 2 and 3

#define UP 5
#define DOWN 12
#define HALF 6
#define RESET 7
#define SWITCH 8
#define red 9
#define green 10
#define blue 11


boolean switched = false;
char c = ' ';               //character to communicate between BT Modules

void setup() {
  //Pins for button inputs and LED outputs
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(SWITCH, INPUT);       //Will be an actual switch and not a button
  pinMode(HALF, INPUT);
  pinMode(RESET, INPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  
  Serial.begin(9600);
  BT.begin(9600);
}

void loop() {
  /*if(digitalRead(UP) == HIGH)
    Serial.println("Up");
  else if(digitalRead(DOWN) == HIGH)
    Serial.println("Down");
  delay(50);*/

  switch(digitalRead(SWITCH))
  {
    case HIGH:  //Serial.println("RED");
                RGB_color(0, 0, 5);
                switched = true;
                break;
    case LOW:   //Serial.println("BLUE");
                RGB_color(5, 0, 0);
                switched = false;
                break;
  }

  switch(switched)
  {
                //For Blue
    case true:  if(digitalRead(HALF) == HIGH)
                {
                  c = 'Q';
                  Serial.println(c);
                  BT.write(c);
                  delay(150);
                }

                else if(digitalRead(RESET) == HIGH)
                {
                  c = 'W';
                  Serial.println(c);
                  BT.write(c);
                  delay(150);
                }

                else if(digitalRead(UP) == HIGH)
                {
                  c = 'E';
                  Serial.println(c);
                  BT.write(c);
                  delay(150);
                }

                else if(digitalRead(DOWN) == HIGH)
                {
                  c = 'R';
                  Serial.println(c);
                  BT.write(c);
                  delay(150);
                }
                break;
    case false:
                //For Red, different signals
                if(digitalRead(HALF) == HIGH)
                {
                  c = 'T';
                  Serial.println(c);
                  BT.write(c);
                  delay(150);
                }

                else if(digitalRead(RESET) == HIGH)
                {
                  c = 'W';
                  Serial.println(c);
                  BT.write(c);
                  delay(150);
                }

                else if(digitalRead(UP) == HIGH)
                {
                  c = 'U';
                  Serial.println(c);
                  BT.write(c);
                  delay(150);
                }

                else if(digitalRead(DOWN) == HIGH)
                {
                  c = 'I';
                  Serial.println(c);
                  BT.write(c);
                  delay(150);
                }
                break;
  }
}

void RGB_color(int redLED, int greenLED, int blueLED)
{
  analogWrite(red, redLED);
  analogWrite(green, greenLED);
  analogWrite(blue, blueLED);
}
