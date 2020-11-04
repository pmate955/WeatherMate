
#include <UTFTGLUE.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>
#define MINPRESSURE 100
#define MAXPRESSURE 1000

const int XP=7,XM=A1,YP=A2,YM=6;
const int TS_LEFT=328,TS_RT=731,TS_TOP=226,TS_BOT=934;
int xTouch, yTouch;

UTFTGLUE tft(0,A2,A1,A3,A4,A0); 
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
Adafruit_GFX_Button prevBtn, nextBtn;

#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define GREY    0x8410
#define CYAN    0x07FF

#define PREV_COLOR 0xD145
#define NEXT_COLOR 0xb07620 
#define OUTLINE_COLOR 0x8410

#define STORE_SIZE 300
#define MAX_MENU_PAGE 3

short inTemps[STORE_SIZE];   //Use short instead of float, because of memory usage
short outTemps[STORE_SIZE];
short inHumidity[STORE_SIZE];
short outHumidity[STORE_SIZE];
short pressure[STORE_SIZE];

int year;
byte month;
byte day;

byte hour;
byte minute;
byte second;

byte displayPage;

void printAll() {
  tft.setTextColor(RED, GREY);
  tft.setTextSize(4);
  tft.print(getTimeString(), CENTER, 1);
  tft.print(" " + String(displayPage), CENTER, 20);
  tft.setColor(255, 0, 0);
  if(second % 3 == 0) {
    shiftData();
    readSensorData();
    tft.setColor(153, 153, 140);
    tft.drawRect(8, 99, 311, 151);
    tft.drawRect(8, 169, 311, 221); 
    tft.setColor(255, 0, 0);
    printTemps();
  } 
}

void setup()
{
  randomSeed(analogRead(0));
  initTime();
  tft.InitLCD();
  tft.setFont(SmallFont);
  tft.clrScr();
  generateDatas();
  displayPage = 0;
  prevBtn.initButton(&tft,  25, 20, 50, 35, OUTLINE_COLOR, PREV_COLOR, BLACK, "PREV", 1);
  nextBtn.initButton(&tft,  25, 60, 50, 35, OUTLINE_COLOR, NEXT_COLOR, BLACK, "NEXT", 1);
  prevBtn.drawButton(false);
  nextBtn.drawButton(false);
}

void loop()
{
  checkPress();
  if(millis() % 1000 == 0) {
    increaseTime();
    printAll();   
  }
}
