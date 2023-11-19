// Функция отправки данных по протоколу MQTT

void MQTT_send_data(String topic, float data){
          String top  = settings.mqtt_topic;
                 top +="/"+ topic;
         String input = settings.mqtt_serv;
         int colonIndex = input.indexOf(':');
         String ipAddress;
         String port;

        if (colonIndex != -1) {
             ipAddress = input.substring(0, colonIndex);
             port = input.substring(colonIndex + 1);
          }
       
  if(settings.mqtt_en && WiFi.status() == WL_CONNECTED){
      client.setServer(ipAddress.c_str(), port.toInt());
      client.loop();
           if(client.connected()){
          count_rf = 0;
                 client.publish(top.c_str(), String(data).c_str());  
           }else{
              count_rf++;
              if (client.connect(settings.mqtt_id.c_str(), settings.mqtt_user.c_str(), settings.mqtt_passw.c_str())){           
                    client.publish(top.c_str(), String(data).c_str());
                }else{
                  if(count_rf > 2){
                     WiFi.disconnect();
                     WiFi.begin(settings.mySSID, settings.myPW);
                     count_rf = 0;
                }
            }
        }
     }
}

String MQTT_status(){
    String response_message = "";
    if(client.connected()){
       response_message = "подключен";
      }else{
       response_message = "отключен";
    }
    return response_message;
} 
