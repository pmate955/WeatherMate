void initSensor() {
    while(!Serial);    // time to get serial running
    unsigned status;
    status = bme.begin(0x76);  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }
}

String readSensorData() {
  initSensor();
  short temp = (short)(bme.readTemperature() * 10);
  short humidity = (short)(bme.readHumidity() * 10);
  return "@" + String(temp) + "H" + String(humidity) + "END";
}
