

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
