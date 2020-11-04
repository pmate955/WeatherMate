
void getMinMax(short* temps, float* minMax) {
  float max = temps[0];
  float min = temps[0];
  for(int i = 0; i < STORE_SIZE; i++) {
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
  for(int x = STORE_SIZE - 1; x >= 0; x--) {
    int sizeIn =  (int)((inTemps[x] - minMaxIn[0]) / deltaIn);
    int sizeOut =  (int)((outTemps[x] - minMaxOut[0]) / deltaOut);
    tft.setColor (0,0,0);
    tft.drawLine(x + 10, 220, x + 10, 170); 
    tft.drawLine(x + 10, 150, x + 10, 100); 
    tft.setColor (0,255,255);
    tft.drawLine(x + 10, 220, x + 10, 220 - sizeIn);
    tft.drawLine(x + 10, 150, x + 10, 150 - sizeOut);
     checkPress();
  }
  tft.setColor(50, 50, 200);
  tft.print("Min: " + String(minMaxIn[0] / 10), LEFT, 230);
  tft.print("Min: " + String(minMaxOut[0] / 10), LEFT, 160);
  tft.setColor(250, 50, 20);
  tft.print("Max: " + String(minMaxIn[1] / 10), RIGHT, 230);
  tft.print("Max: " + String(minMaxOut[1] / 10), RIGHT, 160);
}
