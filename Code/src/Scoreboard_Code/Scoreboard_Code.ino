#include "Pins.h"
#include "CustomFrame.h"
#include <RGBmatrixPanel.h>

RGBmatrixPanel matrix = RGBmatrixPanel(A, B, C, D, CLK, LAT, OE, false, 64);

CustomFrame cFrame = CustomFrame(matrix);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start...");
  matrix.begin();

  cFrame.displayFrame(matrix, "bballNR.txt");
}

void loop() {
  delay(5000);
  cFrame.displayFrame(matrix, "gabe.txt");
  delay(5000);
  cFrame.displayFrame(matrix, "bballNR.txt");
}
