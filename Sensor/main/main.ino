#include "SoftwareSerial.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "WiFiEsp.h"
#include "WiFiEspClient.h"
#include <LowPower.h>

SoftwareSerial Serial1(6, 7);

char ssid[] = "WeatherMate";           
char pass[] = "asdasdasd";     
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "192.168.4.1";
WiFiEspClient client;
Adafruit_BME280 bme;
short seconds;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial1.begin(9600);
  WiFi.init(&Serial1);
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }
  seconds = 60;
  //mySerial.println("AT+UART_DEF=9600,8,1,0,0");
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  if(seconds >= 60) {
      if(connectWifi()) {
        String data = readSensorData();
        Serial.println("READ" + data);
        sendData(data);
        WiFi.disconnect();
        status =  WL_IDLE_STATUS;
      } else {
        Serial.println("NO CONNECTION");
      }
    seconds = 0;
  }
  digitalWrite(LED_BUILTIN, LOW);
//  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
//               SPI_OFF, USART0_OFF, TWI_OFF);
  delay(8000);
  seconds += 8;
}
