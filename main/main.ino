
#define _ESPLOGLEVEL_ 4
#include <UTFTGLUE.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "WiFiEsp.h"
#include "WiFiEspUdp.h"
#include <Wire.h>
#include "RTClib.h"

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
short inHumiditys[STORE_SIZE];
short outHumiditys[STORE_SIZE];
short pressures[STORE_SIZE];

short inTemp;
short outTemp;
short inHumidity;
short outHumidity;
short pressure;


boolean inValidDatas[STORE_SIZE];
boolean outValidDatas[STORE_SIZE];

int year;
byte month;
byte day;

byte hour;
byte minute;
byte second;

byte lastTimeUpdate;
unsigned long lastScreenUpdate;
byte lastInUpdate;

DS1307 rtc;
Adafruit_BME280 bme;

byte displayPage;
unsigned long timeStamp = 0;

char ssid[] = "Redmi";            // your network SSID (name)
char pass[] = "Zsalmafa";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char timeServer[] = "time.nist.gov";  // NTP server
unsigned int localPort = 2390;        // local port to listen for UDP packets

const int NTP_PACKET_SIZE = 48;  // NTP timestamp is in the first 48 bytes of the message
const int UDP_TIMEOUT = 2000;    // timeout in miliseconds to wait for an UDP packet to arrive

byte packetBuffer[NTP_PACKET_SIZE]; // buffer to hold incoming and outgoing packets

WiFiEspUDP Udp;
WiFiEspServer server(3000);
RingBuffer buf(32);

void printAll(boolean needRepaintAll) {
  if(needRepaintAll) {
    tft.print("              ", CENTER, 85);
    tft.print("              ", LEFT, 225);  
    tft.print("              ", RIGHT, 225); 
    tft.print("              ", LEFT, 155);    
    tft.print("              ", RIGHT, 155);                                                        
  }
  tft.setTextColor(RED, GREY);
  tft.setTextSize(4);
  tft.print(getTimeString(), CENTER, 1);
  tft.print(" " + String(timeStamp), CENTER, 20);
  tft.setColor(255, 0, 0);
  if(minute != lastInUpdate || needRepaintAll) {
    shiftData(true);
    readSensorData();
    tft.setColor(153, 153, 140);
    tft.drawRect(8, 99, 311, 151);
    tft.drawRect(8, 169, 311, 221); 
    tft.setColor(255, 0, 0);
    if(displayPage == 0) {
      printGraph(inTemps, outTemps, 0);
    } else if(displayPage == 1) {
      printGraph(inHumiditys, outHumiditys, 1);
    } else if(displayPage == 2) {
      printGraph(pressures, pressures, 2);
    } 
    lastInUpdate = minute;
  } 
  lastScreenUpdate = millis();
}

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
  WiFi.init(&Serial2);
  if (WiFi.status() == WL_NO_SHIELD) {
    while (true);
  }
  WiFi.beginAP("WeatherMate", 3, "asdasdasd", 4, false);
  randomSeed(analogRead(0));
  initTime();
  tft.InitLCD();
  tft.setFont(SmallFont);
  tft.clrScr();
  initSensor();
  displayPage = 0;
  prevBtn.initButton(&tft,  25, 20, 50, 35, OUTLINE_COLOR, PREV_COLOR, BLACK, "PREV", 1);
  nextBtn.initButton(&tft,  25, 60, 50, 35, OUTLINE_COLOR, NEXT_COLOR, BLACK, "NEXT", 1);
  prevBtn.drawButton(false);
  nextBtn.drawButton(false);
  printAll(true);
  server.begin();
}

void loop()
{
  if(hour % 6 == 0 && lastTimeUpdate != hour) {
    timeStamp = getTimeStamp();
    if(timeStamp != 0) rtc.adjust(DateTime(timeStamp));
    lastTimeUpdate = hour;
  }
  checkPress();
  checkRequest();
  if(millis() >= lastScreenUpdate + 500) {
    printAll(false);   
  }
}
