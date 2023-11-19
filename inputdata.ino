void indata(){
     if (captivePortal()) { 
    return;
  }
  if (!validateToken()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
    if (server.hasArg("switch")){  
    String msg;   
      if(server.arg("switch")=="on"){
        settings.mqtt_en = true;
        save_config();
        msg +="<text>Передача данных включена!</text>";
         String input = settings.mqtt_serv;
         int colonIndex = input.indexOf(':');
         String ipAddress;
         String port;

        if (colonIndex != -1) {
             ipAddress = input.substring(0, colonIndex);
             port = input.substring(colonIndex + 1);
          }
        client.setServer(ipAddress.c_str(), port.toInt());
        }else if(server.arg("switch")=="off"){
        settings.mqtt_en = false;
        save_config();
        msg +="<text>Передача данных выключена!</text>";
    } 
    server.send(200, "text/html", msg);
  }
  
    if (server.hasArg("switchjson")){  
    String top;   
      if(server.arg("switchjson")=="on"){
         settings.json_en = true;
         save_config();
        top +="<text><b>Топик: "+ String(settings.mqtt_topic)+"/jsondata</b></text><br>";
      
        }else if(server.arg("switchjson")=="off"){
        settings.json_en = false;
        save_config();
      String topics[] = { String(settings.mqtt_topic)+"/CP10s", String(settings.mqtt_topic)+"/CP1m", String(settings.mqtt_topic)+"/CP5m", String(settings.mqtt_topic)+"/CP60m", String(settings.mqtt_topic)+"/val10s", String(settings.mqtt_topic)+"/val1m", String(settings.mqtt_topic)+"/val5m", String(settings.mqtt_topic)+"/val60m"};
      String data[]   = { String(CP10s), String(CP1m), String(CP5m), String(CP60m), String(val10s), String(val1m), String(val5m), String(val60m)};
         for (int i = 0; i < 8; i++) {
             top +="<text><b>Топик: "+topics[i]+"</b> данные: "+ data[i]+"</text><br>";
                }
    } 
    server.send(200, "text/html", top);
  }
 

 if(server.hasArg("IPMQTT") && server.hasArg("PASSWORD")){  
    strncpy(settings.mqtt_serv, server.arg("IPMQTT").c_str(), MAX_STRING_LENGTH);
    settings.mqtt_user     = String(server.arg("USERNAME"));                        // Логин mqtt
    settings.mqtt_passw    = String(server.arg("PASSWORD"));                        // Пароль mqtt
    settings.mqtt_id       = String(server.arg("ID"));                              // Идентификатор mqtt 
    settings.mqtt_topic    = String(server.arg("topicname"));                       // Корень mqtt 
    settings.mqtt_time     = server.arg("times").toInt();                           // Переодичность обмена mqtt .toInt();
    save_config();
    
    String data = "";
    data += "<text> IP адрес сервера MQTT: <b>"+String(settings.mqtt_serv)+"</b></text><br>";
    data += "<text> Логин: <b>"+settings.mqtt_user+"</b></text><br>";
    data += "<text> Идентификатор устройства: <b>"+settings.mqtt_id+"</b></text><br>";
    data += "<text> Имя корня топика: <b>"+settings.mqtt_topic+"</b></text><br>";
    //data += "<text> Периодичность обмена(с): <b>"+String(settings.mqtt_time)+"</b></text><br>";
    data += "<text><b>Данные успешно сохранены!</b></text>";
    server.send(200, "text/html", data);
  }
  
   if(server.hasArg("NEWPASSWORD")){  
       if(server.arg("NEWPASSWORD") != ""){
           settings.passwd = String(server.arg("NEWPASSWORD")); 
           save_config();
    }
   
    String data = "";
    data += "<text><b>Новый пароль успешно сохранён!</b></text>";
    server.send(200, "text/html", data);
  }
  if (server.hasArg("counter_config") && server.hasArg("counter_total") ){     
        settings.counter_coeff = server.arg("counter_config").toInt();
        settings.total         = server.arg("counter_total").toFloat();
        save_config();
        count_total = 0;
        bCP10s      = 0;
        bCP1m       = 0;
        bCP5m       = 0;
        bCP60m      = 0; 
        String data  = "<text><b>Данные успешно сохранены!</b></text><br>";
               data += "<text><b>Установлен коэффициент счетчика: "+String(settings.counter_coeff)+".</b></text><br>";
               data += "<text><b>Текущие показания счетчика: "+String(settings.total)+".</b></text>";
     server.send(200, "text/html", data);
  }
}
