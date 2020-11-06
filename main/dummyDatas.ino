void generateDatas() {
  for(int i = 0; i < STORE_SIZE; i++){
    inTemps[i] = random(20,30) * 10;
    outTemps[i] = random(-10,30) * 10;
    inHumidity[i] = random(50,100) * 10;
    outHumidity[i] = random(0, 100) * 10;
    pressure[i] = random(900,1050) * 10;
  }
}

void shiftData() {
  for(int i = 0; i < STORE_SIZE - 1; i++){
    inTemps[i] = inTemps[i+1];
    outTemps[i] = outTemps[i+1];
    inHumidity[i] = inHumidity[i+1];
    outHumidity[i] = outHumidity[i+1];
    pressure[i] = pressure[i+1];
  }
}

void readSensorData() {
  inTemps[STORE_SIZE - 1] = random(20,30) *10;
  outTemps[STORE_SIZE - 1] = random(-10,30) * 10;
  inHumidity[STORE_SIZE - 1] = random(50,100) * 10;
  outHumidity[STORE_SIZE - 1] = random(0, 100) * 10;
  pressure[STORE_SIZE - 1] = random(900,1050) * 10;
}
