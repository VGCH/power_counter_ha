void handleNotFound() {
    if (captivePortal()) {        
        return;
  }
  String message = "File Not Found\n\n";
         message += "URI: ";
         message += server.uri();
         message += "\nMethod: ";
         message += (server.method() == HTTP_GET) ? "GET" : "POST";
         message += "\nArguments: ";
         message += server.args();
         message += "\n";
   for (uint8_t i = 0; i < server.args(); i++) {
         message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
   }
  server.send(404, "text/plain", message);
}


void handleLogin() {
    if (captivePortal()) {  // If caprive portal redirect instead of displaying the error page.
    return;
  }
  String msg;
  if (server.hasArg("DISCONNECT")) {
      server.sendHeader("Location", "/login");
      server.sendHeader("Cache-Control", "no-cache");
      server.sendHeader("Set-Cookie", "SESSIONID=0");
      server.send(301);
      return;
  }
  if (server.hasArg("PASSWORD")) {
    if (server.arg("PASSWORD") == String(settings.passwd)) {
      String tokenValue = generateToken();
      for (int i = 0; i < 10; i++) {
      if (tokens[i].value == "") {
        tokens[i].value = tokenValue;
        tokens[i].created = millis() / 1000;
        tokens[i].lifetime = TOKEN_LIFETIME;
        break;
      }
    }
      server.sendHeader("Location", "/");
      server.sendHeader("Cache-Control", "no-cache");
      server.sendHeader("Set-Cookie", "SESSIONID="+tokenValue);
      server.send(301);
      return;
    }
    msg = "Ошибка логина или пароля! Попробуйте еще раз.";
  }
 String html = "<html><head><meta charset=\"UTF-8\"><title>Авторизация</title>";
        html += "<style>";
        html += "body {";
        html += "   background: linear-gradient(to bottom, #060345, #023f78, #540110, #013a42, #1f3d6e);";
        html += "}";
        html += "form {";
        html += "  margin: 20px auto 0;";
        html += "  max-width: 500px;";
        html += "  padding: 20px;";
        html += "  border-radius: 10px;";
        html += "  background-color: #fff;";
        html += "}";
        html += "label {";
        html += "  display: block;";
        html += "  margin-bottom: 5px;";
        html += "  font-size: 16px;";
        html += "  color: #07435e;";
        html += "}";
        html += "input[type=text], input[type=password] {";
        html += "  width: 100%;";
        html += "  padding: 10px;";
        html += "  margin-bottom: 15px;";
        html += "  border: 1px solid #ccc;";
        html += "  border-radius: 4px;";
        html += "  box-sizing: border-box;";
        html += "}";
        html += "input[type=submit] {";
        html += "  background-color: #3683c2;";
        html += "  color: white;";
        html += "  padding: 10px 20px;";
        html += "  border: none;";
        html += "  border-radius: 4px;";
        html += "  cursor: pointer;";
        html += "}";
        html += "h2 {";
        html += "  text-align: center;";
        html += "  margin-top: 120px;";
        html += "  font-size: 25px;";
        html += "  color: white;";
        html += "}";
        html += "footer {";
        html += "  text-align: center;";
        html += "  margin-top: 10px;";
        html += "  font-size: 15px;";
        html += "  color: #cbd6f2;";
        html += "}";
        html += "text {";
        html += "  text-align: center;";
        html += "  margin: 15px;";
        html += "  font-size: 20px;";
        html += "  color: #e80505;";
        html += "}";
        html += "</style>";
        html += "</head><body>";
        html += "<h2>Войдите для конфигурации устройства</h2>";
        html += "<form action=\"/login\" method=\"POST\">";
        html += "<label for=\"password\">Пароль:</label><br>";
        html += "<input type=\"password\" id=\"password\" name=\"PASSWORD\" required><br><br>";
        html += "<input type=\"submit\" value=\"Войти\">";
        html += "</form><center><text>" + msg + "</text></center>";
        html += "</body>";
        html += "<footer>© <b>CYBEREX TECH</b>, 2023. Версия микро ПО <b>"+version_code+"</b>. </footer></html>";
  server.send(200, "text/html", html);
}


void wlanPageHandler(){
    if (captivePortal()) { 
    return;
  }
  if (!validateToken()) {
      server.sendHeader("Location", "/login");
      server.sendHeader("Cache-Control", "no-cache");
      server.send(301);
      return;
  }
  if (server.hasArg("ssid")){    
     if (server.hasArg("password")){
          strncpy(settings.mySSID, server.arg("ssid").c_str(), MAX_STRING_LENGTH);
          strncpy(settings.myPW, server.arg("password").c_str(), MAX_STRING_LENGTH);
          save_config();
          WiFi.begin(settings.mySSID, settings.myPW);
    }else{
         strncpy(settings.mySSID, server.arg("ssid").c_str(), MAX_STRING_LENGTH);
         strncpy(settings.myPW, server.arg("password").c_str(), MAX_STRING_LENGTH);
         save_config();
         WiFi.begin(settings.mySSID, settings.myPW);
    }
    
        while(WiFi.status() != WL_CONNECTED){ delay(100); }   
        delay(100);
   }
  
  String html = "<html><head><meta charset=\"UTF-8\"><title>Wi-Fi конфигурация</title>";
        html += "<link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\" />";
        html += "<h2>Настройка беспроводного соединения</h2>";
        html += "<form>"; 
  if (WiFi.status() == WL_CONNECTED){
    IPAddress ip = WiFi.localIP();
    String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
    html += "Устройство подключено к сети "+String(WiFi.SSID())+"<br>";
    html += "Уровень сигнала: "+String(WiFi.RSSI())+" dBi <br>";
    html += "IP адрес подключения: "+String(ipStr)+"<br>";
  }else{
    html += "Устройство отключено от сети<br>";
  }
  
  html += "Для подключения к  Wi-Fi, выберите сеть из списка...</form>";
  
  int ap_count = WiFi.scanNetworks();
  
  if (ap_count == 0){
       html += "Не найдено ниодной беспроводной сети.<br>";
  }else{
       html += "<form method=\"POST\">";
    for (uint8_t ap_idx = 0; ap_idx < ap_count; ap_idx++){
      html += "<input type=\"radio\" name=\"ssid\" value=\"" + String(WiFi.SSID(ap_idx)) + "\"><text>";
      html += "<b>"+String(WiFi.SSID(ap_idx)) + "</b> Уровень сигнала: " + WiFi.RSSI(ap_idx) +" dBi";
      (WiFi.encryptionType(ap_idx) == ENC_TYPE_NONE) ? html += " " : html += " [защищена]";
      html += "</text><br>";
    }
    
    html += "<br>WiFi пароль доступа (если сеть защищена):<br>";
    html += "<input type=\"text\" name=\"password\">";
    html += "<input type=\"submit\" value=\"Подключиться\">";
    html += "</form>";
  }
 
  html += "</body>";
  html += "<center><br><a href=\"/\">Вернуться назад</a><br></center>";
  html += "<footer>© <b>CYBEREX TECH</b>, 2023. Версия микро ПО <b>"+version_code+"</b>.</footer></html>";
  server.send(200, "text/html", html);
}

void change_login_pass(){
 if (!validateToken()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  String html = "<html><head><meta charset=\"UTF-8\"><title>Изменение пароля</title>";
  html += "<link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\" />";
  html += "</head><body>";
  html += "<h2>Изменение пароля</h2>";
  html += "<form id=\"config-form\" >";
  html += "<div id=\"response\">";
  html += "<label for=\"password\">Новый пароль:</label>";
  html += "<input type=\"password\" id=\"password\" name=\"NEWPASSWORD\" placeholder=\"Новый пароль\" required><br>";
  html += "<label for=\"newpassword\">Введите повторно новый пароль:</label>";
  html += "<input type=\"password\" id=\"newpassword\"  placeholder=\"Новый пароль\" required><br><br>";
  html += "<input type=\"submit\" value=\"Изменить\">";
  html += "</div>";
  html += "</form><br>";
  html += "<center><br><a href=\"/\">Вернуться назад</a><br></center>";
  html += "<footer>© <b>CYBEREX TECH</b>, 2023. Версия микро ПО <b>"+version_code+"</b>.</footer></html>";
  html += pass_js;
  html += "</body></html>";
  server.send(200, "text/html", html);
}
