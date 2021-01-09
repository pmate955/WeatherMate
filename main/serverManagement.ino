
boolean checkRequest() {
  WiFiEspClient client = server.available();
  if(client) {
    buf.init();
    String data = "";
    boolean isDataStarted = false;
    while(client.connected()) {
      if (client.available()) {               // if there's bytes to read from the client,
        char c = client.read();               // read a byte, then
        buf.push(c);                          // push it to the ring buffer
        Serial.println("DATA " + String(c));
        if(isDataStarted && c != 'E') {
          data += String(c);
        } else if(isDataStarted){
          processString(data);
          isDataStarted = false;
        }
        if (buf.endsWith("END")) {
          Serial.println("END FOUND");
          sendHttpResponse(client);
          break;
        } else if(buf.endsWith("@")) {
          isDataStarted = true;
        }         
      } 
    }
    client.flush();
    delay(10);
    client.stop();
  }
}

void sendHttpResponse(WiFiEspClient client)
{
  client.print(
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/plain\r\n"
    "Connection: close\r\n"  // the connection will be closed after completion of the response
    "\r\n");
}

void processString(String data) {
  int splitIndex = -1;
  for(int i = 0; i < data.length(); i++) {
    if(data.charAt(i) == 'H') {
      splitIndex = i;
      break;
    }
  }
  if(splitIndex >= 0) {
    outTemp = (short) data.substring(0, splitIndex).toInt();
    outHumidity = (short) data.substring(splitIndex + 1, data.length()).toInt();
    Serial.println("OUTTEMP" + String(outTemp));
    Serial.println("OUTHUM" + String(outHumidity));
    addOutData();
  }
}
