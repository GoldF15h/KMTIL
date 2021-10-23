#include <SPI.h>
#include <bitBangedSPI.h>
#include <MAX7219_Dot_Matrix.h>

MAX7219_Dot_Matrix myDisplay (4, 10);  // 8 chips, and then specify the LOAD pin only
String data;
void setup ()
{
  Serial.begin(9600);
  myDisplay.begin ();
  myDisplay.setIntensity (2);
  myDisplay.sendString ("Hello there");
}  // end of setup

void loop ()
{
  if (Serial.available() > 0) {
    data = Serial.readStringUntil('\n');
    int e = data.indexOf('\r');
    String firstValue = data.substring(0, e);
    myDisplay.sendString(&firstValue[0]);
  }
  Serial.println(data);
  // do whatever here
}  // end of loop
