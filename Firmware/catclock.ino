/*
*/

int hours = 12;
int minutes = 0;
int seconds = 0;
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_SCLK 0
#define TFT_MOSI 1
#define TFT_RST 2
#define TFT_DC 3
#define TFT_CS 4
#define TFT_BL 5
#define WHITE 0xFFFF

class CatClock : public Adafruit_ST7789 {
  public:
  using Adafruit_ST7789::Adafruit_ST7789;
  void exposeOffsets(int8_t col, int8_t row) {
    setColRowStart(col,row);
  }
};

CatClock meow = CatClock(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup() {
Serial.begin(115200);

  meow.init(76,284); //panel size
  meow.exposeOffsets(82,18);
  meow.invertDisplay(false); // the color is flipped
  meow.setRotation(1); //landscape?
  meow.fillScreen(ST77XX_BLACK); //clean screen
  Serial.println("time to roll!");
    meow.setCursor(0,0);
}

void loop() {

  delay(1000); //it like a metronome that keeps the time for us :)
  seconds++;
//this is just rolling over. To keep nice and simple, we stick with military time.
  if (seconds == 60) {
    seconds = 0;
    minutes++;
  }

  if (minutes == 60) {
    minutes = 0;
    hours++;
  }

  if (hours == 24) {
    hours = 0;
  }

  //the screen is 284 * 76, and with size 5 it is 25 wide 35 tall. we need 8 characters (xx:xx:xx) so it will be total 200 pixels. the cursor begin in top left. to get it center horizontally, we put on 42 (284-240)/2. for the vertical, we place anywhere. lets try 16.

meow.setTextSize(5);
  meow.setTextColor(WHITE);
  meow.setCursor(42,16);
//if the numbers are too small, we will be missing a character! lets fix! the code above did the time for us. we now print it out onto the screen to read it
  meow.fillScreen(ST77XX_BLACK);
     if (hours < 10) meow.print("0");
  meow.print(hours);
     if (minutes < 10) meow.print("0");
  meow.print(minutes);
     if (seconds < 10) meow.print("0");
  meow.print(seconds);
 //serial print will send it to the computer when we try testing it out with the real kit!
  Serial.print(hours);
  Serial.print(";");
  Serial.print(minutes);
  Serial.print(";");
  Serial.println(seconds);
}
