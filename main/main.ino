
#include <UTFTGLUE.h>
UTFTGLUE tft(0,A2,A1,A3,A4,A0); 

#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define GREY    0x8410

short inTemps[300];   //Use short instead of float, because of memory usage
short outTemps[300];
short inHumidity[300];
short outHumidity[300];
short pressure[300];

int year;
byte month;
byte day;

byte hour;
byte minute;
byte second;

void generateDatas() {
  for(int i = 0; i < 300; i++){
    inTemps[i] = random(20,30) * 10;
    outTemps[i] = random(-10,30) * 10;
    inHumidity[i] = random(50,100) * 10;
    outHumidity[i] = random(0, 100) * 10;
    pressure[i] = random(900,1050);
  }
}

void shiftData() {
  for(int i = 0; i < 299; i++){
    inTemps[i] = inTemps[i+1];
    outTemps[i] = outTemps[i+1];
    inHumidity[i] = inHumidity[i+1];
    outHumidity[i] = outHumidity[i+1];
    pressure[i] = pressure[i+1];
  }
}

void readSensorData() {
  inTemps[299] = random(20,30) *10;
  outTemps[299] = random(-10,30) * 10;
  inHumidity[299] = random(50,100) * 10;
  outHumidity[299] = random(0, 100) * 10;
  pressure[299] = random(900,1050);
}

void initTime() {
  year = 2020;
  month = 11;
  day = 3;
  hour = 16;
  minute = 10;
  second = 0;
}

void increaseTime() {
 second++;
  if (second == 60)
  {
    second = 0;
    minute = minute + 1;
  }
  if (minute == 60)
  {
    minute = 0;
    hour = hour + 1;
  }
  if (hour == 24)
  {
    hour = 0;
    day++;
  }  
}

String getTimeString() {
  String out = String(year) + "/" + month + "/" + day + " ";
  out += (hour < 10 ? "0" : "") + String(hour) + ":";
  out += (minute < 10 ? "0" : "") + String(minute) + ":";
  out += (second < 10 ? "0" : "") + String(second);
  return out;
}


void getMinMax(short* temps, float* minMax) {
  float max = temps[0];
  float min = temps[0];
  for(int i = 0; i < 300; i++) {
    if(temps[i] < min) min = temps[i];
    if(temps[i] > max) max = temps[i];
  }
  minMax[0] = min;
  minMax[1] = max;
}

void printTemps() {
  float minMaxIn[2]; 
  float minMaxOut[2];
  getMinMax(inTemps, minMaxIn);
  getMinMax(outTemps, minMaxOut);
  float deltaIn = (minMaxIn[1] - minMaxIn[0]) / 50;
  float deltaOut = (minMaxOut[1] - minMaxOut[0]) / 50;
  tft.setColor(245, 245, 60);
  tft.print("Temperature", CENTER, 90);
  tft.print("IN", CENTER, 230);
  tft.print("OUT", CENTER, 160);
  for(int x = 299; x >= 0; x--) {
    int sizeIn =  (int)((inTemps[x] - minMaxIn[0]) / deltaIn);
    int sizeOut =  (int)((outTemps[x] - minMaxOut[0]) / deltaOut);
    tft.setColor (0,0,0);
    tft.drawLine(x+10, 220, x+10, 170); 
    tft.drawLine(x+10, 150, x+10, 100); 
    tft.setColor (0,255,255);
    tft.drawLine(x + 10, 220, x + 10, 220 - sizeIn);
    tft.drawLine(x + 10, 150, x + 10, 150 - sizeOut);
  }
  tft.setColor(50, 50, 200);
  tft.print("Min: " + String(minMaxIn[0] / 10), LEFT, 230);
  tft.print("Min: " + String(minMaxOut[0] / 10), LEFT, 160);
  tft.setColor(250, 50, 20);
  tft.print("Max: " + String(minMaxIn[1] / 10), RIGHT, 230);
  tft.print("Max: " + String(minMaxOut[1] / 10), RIGHT, 160);


}

void setup()
{
  randomSeed(analogRead(0));
  initTime();
  tft.InitLCD();
  tft.setFont(SmallFont);
  tft.clrScr();
  generateDatas();
}

void loop()
{
  increaseTime();
  tft.setTextColor(RED, GREY);
  tft.setTextSize(4);
  tft.print(getTimeString(), CENTER, 1);
  tft.setColor(255, 0, 0);
  if(second % 3 == 0) {
    shiftData();
    readSensorData();
    printTemps();
  }
  delay(1000);
}
