void SSDP_init(){
   String ipStr;
     if (WiFi.status() == WL_CONNECTED){
          IPAddress ip = WiFi.localIP();
          ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
             }else{
          ipStr = "10.10.20.1";
       }
         SSDP.setSchemaURL("description.xml");
         SSDP.setHTTPPort(80);
         SSDP.setName("IoT Power Meter [CYBEREX Tech]");
         SSDP.setSerialNumber(String(ESP.getChipId()));
         SSDP.setURL("http://"+ipStr+"/");
         SSDP.setModelName("IoT Power Meter");
         SSDP.setModelNumber(version_code);
         SSDP.setModelURL("https://cyberex.online");
         SSDP.setManufacturer("V.G.C. Smart Electronics");
         SSDP.setManufacturerURL("https://cyberex.online");
         SSDP.begin();
}
