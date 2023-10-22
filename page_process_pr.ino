void page_process(){
   String input = server.arg("page");
       if (input == "wlan_config"){
               wlanPageHandler();
         }else if(input == "send_config"){
               send_config();
         }else if(input == "changelp"){
               change_login_pass();
         }else if(input == "update_fw"){
               update_fw_page();
         }else if(input == "indata"){
               indata();
         }else if(input == "time"){
                  time_work();
         }else if(input == "coeftube"){
                  tube_setting();
         }else if(input == "dev_reboot"){
               dev_reboot();
         }else{
             handleRoot();
     }
}

void dev_reboot(){
   if (captivePortal()) {
      return;
  }
  String header;
  if (validateToken()){
       save_config();
       stat_reboot = true; 
       reboot_t = millis();
       server.send(200, "text", "ок");   
  }   
}

void reboot_dev_delay(){
  if(stat_reboot && (millis() - reboot_t) > 2000){
       ESP.restart();
  } 
}
