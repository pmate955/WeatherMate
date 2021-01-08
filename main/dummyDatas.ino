void generateDatas() {
  for(int i = 0; i < STORE_SIZE; i++){
    inTemps[i] = random(20,30) * 10;
    outTemps[i] = random(-10,30) * 10;
    inHumidity[i] = random(50,100) * 10;
    outHumidity[i] = random(0, 100) * 10;
    pressure[i] = random(900,1050) * 10;
  }
}
