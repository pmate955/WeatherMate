
boolean connectWifi() {
  while ( status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
  }
  return status == WL_CONNECTED;
}

void sendData(String data) {
  if (client.connect(server, 3000)) {
    client.println("POST / HTTP/1.1");
    client.println("Host: arduino.cc");
    client.println("Connection: close");
    client.println("data: " + data);
    client.println();
    client.flush();
    delay(2000);
    client.stop();
  }
}
