/*
  An example showing rainbow colours on a 1.8" TFT LCD screen
  and to show a basic example of font use.

  Make sure all the display driver and pin connections are correct by
  editing the User_Setup.h file in the TFT_eSPI library folder.

  Note that yield() or delay(0) must be called in long duration for/while
  loops to stop the ESP8266 watchdog triggering.

  #########################################################################
  ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
  #########################################################################
*/

#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include "pin_config.h"

#define SHOW_DATA

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h
//TFT_eSprite sprite = TFT_eSprite(&tft);
unsigned short imageS[256] = {0}; // edit this screenW * screen H

unsigned long targetTime = 0;
byte state = 0;
uint32_t runing = 0;
uint16_t color = TFT_GREEN;

const int clockPin = 0; // digital pin 2
const int ledPin = 13;
const int dataPin = 14;
const int testPin = 11; 
int i = 0;
int x = 0;
int y = 100;
int dataState = 0;

int screenW = 0;
int screenH = 0;

const int ledChannel = 0;
const int freq = 5000;
const int resolution = 8;   // 8 bits
const int brightness = 128; // 8 bits 0 ..
void setup(void)
{
    Serial.begin(115200);

    //sprite.createSprite(32, 32);
    //sprite.setSwapBytes(true);


    pinMode(PIN_POWER_ON, OUTPUT);
    digitalWrite(PIN_POWER_ON, HIGH);

    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    screenH = tft.height();
    screenW = tft.width();
    //tft.fillScreen(TFT_RED); delay(300);
    //tft.fillScreen(TFT_GREEN); delay(300);
    tft.fillScreen(TFT_BLUE); delay(300);

    targetTime = millis() + 1000;

    //sprite.pushImage(0, 0, 16, 16, imageS);
    //sprite.pushSprite(100, 100);

    pinMode(clockPin, INPUT_PULLUP);
    pinMode(dataPin, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
    pinMode(testPin, OUTPUT);
    attachInterrupt(clockPin, pin2Interrupt_F, FALLING);
    attachInterrupt(dataPin, pin2Interrupt_R, FALLING);

    ledcSetup(ledChannel, freq, resolution); // 0-15, 5000, 8
    ledcAttachPin(TFT_BL, ledChannel); // TFT_BL, 0 - 15
    ledcWrite(ledChannel, brightness); // 0-15, 0-255 (with 8 bit resolution)
    // The standard ADAFruit font still works as before
    tft.setTextColor(TFT_WHITE);
    tft.drawCentreString("NIKON Speedlight simulator", 80, 0, 2);
}

void pin2Interrupt_R(void)
{
  Serial.println("Rising");
  digitalWrite(testPin, HIGH);
  dataState = digitalRead(dataPin);
  dataState = 1;
  digitalWrite(testPin, LOW);
}

void pin2Interrupt_F(void)
{
  Serial.println("Falling");
  digitalWrite(testPin, HIGH);
  dataState = digitalRead(dataPin);
  dataState = 0;
  digitalWrite(testPin, LOW);
}

void loop()
{
    //delay(1);
    if (millis() > runing) {
        //Serial.print("Current running ");
        //Serial.print(millis());
        //Serial.println(" millis");
        runing = millis() + 1000;
    }
    if (targetTime < millis()) 
    {
        targetTime = millis() + 5;

        // Colour changing state machine
        //for (int i = 0; i < tft.width(); i++) {
        //    tft.drawFastVLine(i, 0, tft.height(), colour);
        //    switch (state) {
        //    case 0:
        //        green += 2;
        //        if (green == 64) {
        //            green = 63;
        //            state = 1;
        //        }
        //        break;
        //    case 1:
        //        red--;
        //        if (red == 255) {
        //            red = 0;
        //            state = 2;
        //        }
        //        break;
        //    case 2:
        //        blue ++;
        //        if (blue == 32) {
        //            blue = 31;
        //            state = 3;
        //        }
        //        break;
        //    case 3:
        //        green -= 2;
        //        if (green == 255) {
        //            green = 0;
        //            state = 4;
        //        }
        //        break;
        //    case 4:
        //        red ++;
        //        if (red == 32) {
        //            red = 31;
        //            state = 5;
        //        }
        //        break;
        //    case 5:
        //        blue --;
        //        if (blue == 255) {
        //            blue = 0;
        //            state = 0;
        //        }
        //        break;
        //    }
        //    colour = red << 11 | green << 5 | blue;
        //}


        // The new larger fonts do not use the .setCursor call, coords are embedded
        //+tft.setTextColor(TFT_BLACK, TFT_BLACK); // Do not plot the background colour

        // Overlay the black text on top of the rainbow plot (the advantage of not drawing the backgorund colour!)
        //tft.drawCentreString("Font size 2", 80, 14, 2); // Draw text centre at position 80, 12 using font 2

        //tft.drawCentreString("Font size 2",81,12,2); // Draw text centre at position 80, 12 using font 2

        //tft.drawCentreString("Font size 4", 80, 30, 4); // Draw text centre at position 80, 24 using font 4

        //tft.drawCentreString("12.34", 80, 54, 6); // Draw text centre at position 80, 24 using font 6

        //tft.drawCentreString("12.34 is in font size 6", 80, 92, 2); // Draw text centre at position 80, 90 using font 2

        // Note the x position is the top left of the font!

        // draw a floating point number
        //float pi = 3.14159; // Value to print
        //int precision = 3;  // Number of digits after decimal point
        //int xpos = 50;      // x position
        //int ypos = 30;     // y position
        //int font = 2;       // font number only 2,4,6,7 valid. Font 6 only contains characters [space] 0 1 2 3 4 5 6 7 8 9 0 : a p m
        //xpos += tft.drawFloat(pi, precision, xpos, ypos, font); // Draw rounded number and return new xpos delta for next print position

        //tft.drawString(" is pi", xpos, ypos, font); // Continue printing from new x position
        //tft.drawString(" is pi", xpos, ypos, font); // Continue printing from new x position
#ifdef SHOW_DATA
        tft.drawPixel(x,y+dataState,color);
        if (x < screenW)
        {
            x = x + 1;
        }
        else
        {
            x = 0;
            if (y < screenH)
            {
                y = y + 4;
            //tft.drawLine(0,y-5,319,y-5,TFT_BLUE);
            //tft.drawLine(0,y,319,y,TFT_BLUE);
            //tft.drawLine(0,y+5,319,y+5,TFT_BLUE);
            }
            else
            {
                y=0;
                if (color == TFT_GREEN)
                {
                    color = TFT_RED;
                }
                else
                {
                    color = TFT_GREEN;
                }
            //tft.drawLine(0,y-5,319,y-5,TFT_BLUE);
            //tft.drawLine(0,y,319,y,TFT_BLUE);
            //tft.drawLine(0,y+5,319,y+5,TFT_BLUE);
            }
        }
#endif
    }
}


// TFT Pin check
#if PIN_LCD_WR  != TFT_WR || \
    PIN_LCD_RD  != TFT_RD || \
    PIN_LCD_CS    != TFT_CS   || \
    PIN_LCD_DC    != TFT_DC   || \
    PIN_LCD_RES   != TFT_RST  || \
    PIN_LCD_D0   != TFT_D0  || \
    PIN_LCD_D1   != TFT_D1  || \
    PIN_LCD_D2   != TFT_D2  || \
    PIN_LCD_D3   != TFT_D3  || \
    PIN_LCD_D4   != TFT_D4  || \
    PIN_LCD_D5   != TFT_D5  || \
    PIN_LCD_D6   != TFT_D6  || \
    PIN_LCD_D7   != TFT_D7  || \
    PIN_LCD_BL   != TFT_BL  || \
    TFT_BACKLIGHT_ON   != HIGH  || \
    170   != TFT_WIDTH  || \
    320   != TFT_HEIGHT
#error  "Error! Please make sure <User_Setups/Setup206_LilyGo_T_Display_S3.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#error  "Error! Please make sure <User_Setups/Setup206_LilyGo_T_Display_S3.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#error  "Error! Please make sure <User_Setups/Setup206_LilyGo_T_Display_S3.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#error  "Error! Please make sure <User_Setups/Setup206_LilyGo_T_Display_S3.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#endif

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5,0,0)
#error  "The current version is not supported for the time being, please use a version below Arduino ESP32 3.0"
#endif




