
String getUnit(byte dataType) {
   if(dataType == 0){
    tft.print("Temperature", CENTER, 85);
    return "°C"; 
  } else if(dataType == 1) {
    tft.print("Humidity", CENTER, 85); 
    return "%";
  } else if(dataType == 2) {
    tft.print("Air pressure", CENTER, 85); 
    return "hPa";
  }
}

void getMinMax(short* temps, float* minMax, boolean isInside) {
  float max = temps[0];
  float min = temps[0];
  for(int i = 0; i < STORE_SIZE; i++) {
    if((isInside && !inValidDatas[i]) || (!isInside && !outValidDatas[i])) continue;  
    if(temps[i] < min) min = temps[i];
    if(temps[i] > max) max = temps[i];
  }
  minMax[0] = min;
  minMax[1] = max;
}

void printGraph(short* inData, short* outData, byte dataType) {
  float minMaxIn[2]; 
  float minMaxOut[2];
  getMinMax(inData, minMaxIn, true);
  getMinMax(outData, minMaxOut, false);
  float deltaIn = (minMaxIn[1] - minMaxIn[0]) / 50;
  float deltaOut = (minMaxOut[1] - minMaxOut[0]) / 50;
  tft.setColor(245, 245, 60);
  String unit = getUnit(dataType); 
  tft.print("IN", CENTER, 225);
  tft.print("OUT", CENTER, 155);
  tft.setColor(50, 50, 200);
  tft.print("Min: " + String(minMaxIn[0] / 10) + unit, LEFT, 225);
  tft.print("Min: " + String(minMaxOut[0] / 10) + unit, LEFT, 155);
  tft.setColor(250, 50, 20);
  tft.print("Max: " + String(minMaxIn[1] / 10) + unit, RIGHT, 225);
  tft.print("Max: " + String(minMaxOut[1] / 10) + unit, RIGHT, 155);
  int ctr = 0;
  for(int x = STORE_SIZE - 1; x >= 0; x--) {
    int sizeIn =  (int)((inData[x] - minMaxIn[0]) / deltaIn);
    int sizeOut =  (int)((outData[x] - minMaxOut[0]) / deltaOut);
    tft.setColor (0,0,0);
    tft.drawLine(x + 10, 220, x + 10, 170); 
    tft.drawLine(x + 10, 150, x + 10, 100); 
    tft.setColor (31,86,148);
    if(inValidDatas[x]) tft.drawLine(x + 10, 220, x + 10, 220 - sizeIn);
    if(outValidDatas[x]) tft.drawLine(x + 10, 150, x + 10, 150 - sizeOut);
    if(ctr % 24 == 0) {
      tft.setColor(153, 153, 140);
      tft.drawLine(x + 10, 150, x + 10, 153);
      tft.drawLine(x + 10, 220, x + 10, 223);
    }
    ctr++;
    checkPress();
  }
}
