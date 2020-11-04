bool isTouched(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        xTouch = map(p.y, 226, 934, 0, 320); //.kbv makes sense to me
        yTouch = map(p.x, 731, 328, 0, 240);
    }
    return pressed;
}

void checkPress() {
  bool down = isTouched();
  prevBtn.press(down & prevBtn.contains(xTouch, yTouch));
  nextBtn.press(down & nextBtn.contains(xTouch, yTouch));
  if (prevBtn.justReleased() && displayPage > 0)
      prevBtn.drawButton(false);
  if (nextBtn.justReleased() && displayPage < MAX_MENU_PAGE)
      nextBtn.drawButton(false);
  if (prevBtn.justPressed()) {
      if(displayPage > 0) {
        displayPage--;
        nextBtn.drawButton(false);
      }
      prevBtn.drawButton(displayPage == 0);
      printAll();
  }
  if (nextBtn.justPressed()) {
      if(displayPage < MAX_MENU_PAGE) {
        displayPage++;
        prevBtn.drawButton(false);
      }
      nextBtn.drawButton(displayPage == MAX_MENU_PAGE);
      printAll();
  }    

}
