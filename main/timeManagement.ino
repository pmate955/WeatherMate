

void initTime() {
  Wire.begin();
  rtc.begin();
  if (!rtc.isrunning()) {
    timeStamp = getTimeStamp();
    rtc.adjust(DateTime(timeStamp));
  }
  setTimeValues();
}

void setTimeValues() {
  DateTime now = rtc.now();
  year = now.year();
  month = now.month();
  day = now.day();
  hour = now.hour();
  minute = now.minute();
  second = now.second();
}

String getTimeString() {
  setTimeValues();
  String out = String(year) + "/" + month + "/" + day + " ";
  out += (hour < 10 ? "0" : "") + String(hour) + ":";
  out += (minute < 10 ? "0" : "") + String(minute) + ":";
  out += (second < 10 ? "0" : "") + String(second);
  return out;
}
