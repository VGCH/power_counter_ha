void send_config(){
 if (!validateToken()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  String html = "<html><head><meta charset=\"UTF-8\"><title>Передача данных</title>";
  html += "<link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\" />";
  html += "</head><body>";
  html += "<h2>Конфигурация передачи данных (MQTT)</h2>";
  html += "<form>";
  html += "<input type=\"checkbox\" id=\"switch\" "+mqtt_act()+"><text> Активировать передачу данных</text><br>";
 // html += "<input type=\"checkbox\" id=\"switchjson\" "+json_act()+" ><text> Использовать формат JSON </text>";
  html += "<div id=\"response2\">"+status_mqtt_en()+"</div><br>";
  html += "<div class=\"spoiler\"><input type=\"checkbox\" id=\"spoiler1\">";
  html += "<label for=\"spoiler1\">Посмотреть текущую конфигурацию</label>";
  html += "<div id=\"response21\">"+full_cong()+"</div></div>";
  html +=" </form>";
  html += "<form id=\"config-form\" >";
  html += "<div id=\"response\">";
  html += "<label for=\"ip\">IP адрес сервера MQTT:</label>";
  html += "<input type=\"text\" id=\"ip\" name=\"IPMQTT\" placeholder=\"192.168.1.2:1883\" pattern=\"^((\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.){3}(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5]):(\\d{1,5})$\" value=\""+String(settings.mqtt_serv)+"\" required><br>";
  html += "<label for=\"login\">Логин:</label>";
  html += "<input type=\"text\" id=\"login\" name=\"USERNAME\" placeholder=\"Логин MQTT\" value=\""+settings.mqtt_user+"\" required><br>";
  html += "<label for=\"password\">Пароль:</label>";
  html += "<input type=\"password\" id=\"password\" name=\"PASSWORD\" placeholder=\"Пароль MQTT\" required><br>";
  html += "<label for=\"id\">Идентификатор устройства:</label>";
  html += "<input type=\"text\" id=\"id\" name=\"ID\" placeholder=\"Идентификатор устройства\" value=\""+settings.mqtt_id+"\" required><br>";
  html += "<label for=\"topic\">Корень топика:</label>";
  html += "<input type=\"text\" id=\"topic\" name=\"topicname\" placeholder=\"Пример: [имя_топика]/temp\"  value=\""+settings.mqtt_topic+"\" required><br>";
 // html += "<label for=\"number\">Периодичность обмена(с):</label>";
 // html += "<input type=\"number\" id=\"number\" name=\"times\" placeholder=\"Пример: 60\" pattern=\"[0-9]{4,}\" value=\""+String(settings.mqtt_time)+"\" required><br><br>";
  html += "<input type=\"submit\" value=\"Сохранить\">";
  html += "</div>";
  html += "</form><br>";
  html += "<center><br><a href=\"/\">Вернуться назад</a><br></center>";
  html += "<footer>© <b>CYBEREX TECH</b>, 2023. Версия микро ПО <b>"+version_code+"</b>. </footer>";
  html += config_js;
  html += "</body></html>";
  server.send(200, "text/html", html);
}

String mqtt_act(){
String rt ="";
  if(settings.mqtt_en){
    rt = "checked";
  }
  return rt;
}
String json_act(){
String rt ="";
  if(settings.json_en){
    rt = "checked";
  }
  return rt;
}
String full_cong(){
    String data = "";
    data += "<text> IP адрес сервера MQTT: <b>"+String(settings.mqtt_serv)+"</b></text><br>";
    data += "<text> Логин: <b>"+settings.mqtt_user+"</b></text><br>";
    data += "<text> Идентификатор устройства: <b>"+settings.mqtt_id+"</b></text><br>";
    data += "<text> Имя корня топика: <b>"+settings.mqtt_topic+"</b></text><br>";
    //data += "<text> Периодичность обмена(с): <b>"+String(settings.mqtt_time)+"</b></text><br>";
    return data;
}
String status_mqtt_en(){
  String data = "<text>Передача данных отключена.</text>";
  if(settings.mqtt_en){
    data = "<text>Передача данных включена.</text>";
  }
  return data;
}
