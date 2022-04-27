#include <Wire.h>  // Include Wire if you're using I2C
#include <SPI.h>  // Include SPI if you're using SPI
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library
 
// Also connect pin 13 to SCK and pin 11 to MOSI
#define OLED_MOSI   23
#define OLED_CLK    18
#define OLED_DC     16
#define OLED_CS     5
#define OLED_RESET  17
 
const int piezoPin = 13;
 
// these variables will change:
int sensorReading = 0;      // variable to store the value read from the sensor pin

// Declare a MicroOLED object. The parameters include:
// 1 - Reset pin: Any digital pin
// 2 - D/C pin: Any digital pin (SPI mode only)
// 3 - CS pin: Any digital pin (SPI mode only, 10 recommended)
MicroOLED oled(OLED_RESET, OLED_DC, OLED_CS);
 
void setup()
{
  delay(100);
  oled.begin();    // Initialize the OLED
  oled.clear(ALL); // Clear the display's internal memory
  oled.clear(PAGE); // Clear the buffer.
  randomSeed(analogRead(A0));
  writeSplashScreen();
}
 
void loop()
{
  sensorReading = analogRead(13);
  if (sensorReading > 90)
  {
    printTitle("FINGER!", 1);
  }
  else
  {
    writeSexyText("Clear");
  }
  delay(500);
}
 
// Center and print a small title
// This function is quick and dirty. Only works for titles one
// line long.
void printTitle(String title, int font)
{
  int middleX = oled.getLCDWidth() / 2;
  int middleY = oled.getLCDHeight() / 2;
 
  oled.clear(PAGE);
  oled.setFontType(font);
  // Try to set the cursor in the middle of the screen
  oled.setCursor(middleX - (oled.getFontWidth() * (title.length() / 2)),
                 middleY - (oled.getFontHeight() / 2));
  // Print the title:
  oled.print(title);
  oled.display();
  delay(1500);
  oled.clear(PAGE);
}
 
void writeSexyText(String text){
  oled.clear(PAGE);
  oled.rect(0,0,64,48);
  oled.setCursor(2,2);
  oled.printf(text.c_str()); //why the hell do c-like languages still exist
  oled.display();
}
 
void writeSplashScreen(){
  const char *lines[] = {
    "AlexOS"
  };
 
  oled.clear(PAGE);
  oled.rect(0,0,64,48);
  oled.setCursor(2,2);
 
  for(int i = 0; i < sizeof(lines); i++)
  {
    oled.println(lines[i]);
    oled.display();
    delay(900);
  }
}