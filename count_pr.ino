ICACHE_RAM_ATTR void count_power(){   // Функция вызываемая прерыванием, регистрация импульсов трубки
     bCP10s++;
     bCP1m++;
     bCP5m++;
     bCP60m++; 
     count_total++;
}

void timers(){
   unsigned long currentMillis = millis();  
   if(settings.counter_coeff == 0){
      settings.counter_coeff = 1;
   }
   
     float cf = (float)(1.00/settings.counter_coeff);
     if((currentMillis - t10s) > 10000 || currentMillis < t10s){ // Событие срабатывающее каждые 10 сек 
             val10s  = bCP10s*cf*1000*360;
             t10s    = currentMillis;
             CP10s   = bCP10s;
             bCP10s  = 0;
             MQTT_send_data("10s", val10s);  
        }
        
    if((currentMillis - t60s) > 60000 || currentMillis < t60s){ // Событие срабатывающее каждые 60 сек 
             val1m  = bCP1m*cf*1000*60;
             t60s   = currentMillis;
             CP1m   = bCP1m;
             settings.total = settings.total + (bCP1m*cf); 
             bCP1m  = 0;  
             MQTT_send_data("1m", val1m);  
        }

    if((currentMillis - t5min) > 300000 || currentMillis < t5min){ // Событие срабатывающее каждые 5 мин
              val5m = bCP5m*cf*1000*12;
              t5min = currentMillis;
              CP5m  = bCP5m;
              bCP5m = 0;
              MQTT_send_data("5m", val5m);
              MQTT_send_data("total", settings.total);
        }    
     
    if((currentMillis - t60min) > 3600000 || currentMillis < t60min){ // Событие срабатывающее каждые 60 мин
             val60m = bCP60m*cf*1000;
             t60min = currentMillis;
             CP60m  = bCP60m;
             bCP60m = 0;
             MQTT_send_data("60m", val60m);
             save_config();
              
        }  
  
}


void led_ind(){
    if(digitalRead(SENS)){
          led_stat = true;
          digitalWrite(STATUS_LED, HIGH);
          currentMillisLed = millis();
           }
     if(millis() - currentMillisLed > 100 && led_stat ){
                led_stat = false;
                digitalWrite(STATUS_LED, LOW);
          }     
       
}
