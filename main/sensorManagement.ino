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

void shiftData(boolean inside) {
  for(int i = 0; i < STORE_SIZE - 1; i++){
    if(inside){
      inTemps[i] = inTemps[i+1];
      inHumidity[i] = inHumidity[i+1];
      pressure[i] = pressure[i+1];
      inValidDatas[i] = inValidDatas[i+1];
    } else {
      outTemps[i] = outTemps[i+1];
      outHumidity[i] = outHumidity[i+1];
      outValidDatas[i] = outValidDatas[i+1];
    }  
  }
}

void readSensorData() {
  inTemps[STORE_SIZE - 1] = (short)(bme.readTemperature() * 10);
  inHumidity[STORE_SIZE - 1] = (short)(bme.readHumidity() * 10);
  pressure[STORE_SIZE - 1] = (short)((bme.readPressure() / 100.0F)  * 10);
  inValidDatas[STORE_SIZE - 1] = true;
}
