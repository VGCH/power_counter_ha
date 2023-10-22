// Перенаправление на Captive Portal, если получили запрос на другой домен.
boolean captivePortal() {
  if (!isIp(server.hostHeader()) && server.hostHeader() != (String(myHostname) + ".local")) {
    server.sendHeader("Location", String("http://") + toStringIp(server.client().localIP()), true);
    server.send(302, "text/plain", "");                                                                // Empty content inhibits Content-length header so we have to close the socket ourselves.
    server.client().stop();                                                                            // Stop is needed because we sent no content length
    return true;
    }
  return false;
}

// Проверка является ли строка IP адресом 
boolean isIp(String str) {
  for (size_t i = 0; i < str.length(); i++) {
    int c = str.charAt(i);
    if (c != '.' && (c < '0' || c > '9')) { 
         return false; 
      }
  }
  return true;
}

// Преобразование строки в тип переменной IPAddress
String toStringIp(IPAddress ip) {
    String res = "";
    for (int i = 0; i < 3; i++) {
         res += String((ip >> (8 * i)) & 0xFF) + "."; 
           }
         res += String(((ip >> 8 * 3)) & 0xFF);
   return res;
}

void connectWifi() {
  if(stat_wifi){
  WiFi.begin(settings.mySSID, settings.myPW);
  int connRes = WiFi.waitForConnectResult();
  }
}

void portals(){
   if (connect) {
    connect = false;
    connectWifi();
    lastConnectTry = millis();
  }
    unsigned int s = WiFi.status();
    if (s == 0 && millis() > (lastConnectTry + 60000)) {
         connect = true;
    }
  
    if (status != s) {  // WLAN status change
        status = s;
      if (s == WL_CONNECTED) {
          if (MDNS.begin(myHostname)) {
             MDNS.addService("http", "tcp", 80);
          }
        } 
      }
    if (s == WL_CONNECTED) { 
          MDNS.update(); 
      }
}
