 String millis2time(){ // преобразование миллисекунд в вид д/ч/м/с
  
         int times =(millis()/1000);
         int days =  (times/3600)/24;
         int timehour =(((times)  % 86400L) / 3600); // часы
        if ( ((times % 3600) / 60) < 10 ) {
         int timehour = 0;
               }
         int timeminuts=((times  % 3600) / 60); // минуты
         if ( (times % 60) < 10 ) {
         int timeminuts = 0;
             }
         int timeseconds=(times % 60); // секунды
       String Time= String(days)+":"+String(twoDigits(timehour))+":"+String(twoDigits(timeminuts))+":"+String(twoDigits(timeseconds));
       return Time;
     }

 String twoDigits(int digits){
             if(digits < 10) {
          String i = '0'+String(digits);
          return i;
         }
          else {
        return String(digits);
         }
      }

void time_work(){
   if (captivePortal()) {  
    return;
  }
  String header;
  if (validateToken()){
     String outjson = "{";
     outjson += "\"sensor\":\"Radiation\",";
     outjson += "\"time\":\""+millis2time()+"\",";
     outjson += "\"CP10s\":\""+String(CP10s)+"\",";
     outjson += "\"CP1m\":\""+String(CP1m)+"\",";
     outjson += "\"CP5m\":\""+String(CP5m)+"\",";
     outjson += "\"CP60m\":\""+String(CP60m)+"\",";
     outjson += "\"val10s\":\""+String(val10s)+"\",";
     outjson += "\"val1m\":\""+String(val1m)+"\",";
     outjson += "\"val5m\":\""+String(val5m)+"\",";
     outjson += "\"val60m\":\""+String(val60m)+"\",";
     outjson += "\"PM\":\""+String(settings.total)+"\",";
     outjson += "\"MQTT\":\""+MQTT_status()+"\"";
     outjson += "}";
     server.send(200, "text", outjson);   
  }   
}

String JSON_DATA(){
     String outjson = "{";
     outjson += "\"CP10s\":\""+String(CP10s)+"\",";
     outjson += "\"CP1m\":\""+String(CP1m)+"\",";
     outjson += "\"CP5m\":\""+String(CP5m)+"\",";
     outjson += "\"CP60m\":\""+String(CP60m)+"\",";
     outjson += "\"val10s\":\""+String(val10s)+"\",";
     outjson += "\"val1m\":\""+String(val1m)+"\",";
     outjson += "\"val5m\":\""+String(val5m)+"\",";
     outjson += "\"val60m\":\""+String(val60m)+"\",";
     outjson += "\"PM\":\""+String(settings.total)+"\",";
     outjson += "\"WORKTIME\":\""+String(millis()/1000)+"\"";
     outjson += "}";
     return outjson;
}
