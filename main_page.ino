void handleRoot() {
   if (captivePortal()) {  
    return;
  }
  String header;
  if (!validateToken()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  String html = "<html><head><meta charset=\"UTF-8\"><title>Счетчик электроэнергии</title>";
  html += "<link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\" />";
  html +=  js;
  html += "</head><body>";
  html += divcode;
  html += "<h2> Основные данные счетчика </h2>";
  html += "<form onsubmit=\"return false\" oninput=\"level.value = flevel.valueAsNumber\">";
  String content ="";
  if (server.hasHeader("User-Agent")) {
    content += "the user agent used is : " + server.header("User-Agent") + "<br><br>";
  }
  html += "<text>Время работы устройства:</text> <div class =\"live\" id=\"timew\">00:00:00:00</div>";
  html += "<text>Статус MQTT </text> <div class =\"live\" id=\"MQTT\">"+MQTT_status()+"</div>";
  html += "<text>Потребляемая мощность (сред. 10 сек), Вт*ч:</text> <div class =\"live\" id=\"val10s\">0.00</div>";
  html += "<text>Потребляемая мощность (сред. 1 мин), Вт*ч:</text>  <div class =\"live\" id=\"val1m\" >0.00</div>";
  html += "<text>Потребляемая мощность (сред. 5 мин), Вт*ч:</text>  <div class =\"live\" id=\"val5m\" >0.00</div>";
  html += "<text>Потребляемая мощность (сред. 60 мин), Вт*ч:</text> <div class =\"live\" id=\"val60m\">0.00</div>";
  html += "<text>Импульсов за период 10 сек:</text>  <div class =\"live\" id=\"CP10s\" >0</div>";
  html += "<text>Импульсов за период 1 мин:</text>   <div class =\"live\" id=\"CP1m\"  >0</div>";
  html += "<text>Импульсов за период 5 мин:</text>   <div class =\"live\" id=\"CP5m\"  >0</div>";
  html += "<text>Импульсов за период 60 мин:</text>  <div class =\"live\" id=\"CP60m\" >0</div>";
  html += "<text>Показания счетчика:</text>  <div class =\"livePM\" id=\"PM\" >0000000</div>";
  html += "</form>";
  html += "</body>";
  html += "<center><br><a href=\"/?page=wlan_config\">Wi-Fi конфигурация</a><br>";
  html += "<a href=\"/?page=send_config\">Настройка передачи данных</a><br>";
  html += "<a href=\"/?page=coeftube\">Конфигурация счетчика</a><br>";
  html += "<a href=\"/?page=changelp\">Изменение пароля устройства</a><br>";
  html += "<a href=\"/?page=update_fw\">Обновление прошивки</a><br>";
  html += "<a href=\"javascript:void(0)\" onclick=\"rebootdev()\">Перезагрузить устройство</a><br>";
  html += "<a href=\"/login?DISCONNECT=YES\">Выход</a></center>";
  html += "<footer>© <b>CYBEREX TECH</b>, 2023. Версия микро ПО <b>"+version_code+"</b>.</footer>";
  html += "<script src=\"script.js\"></script>"; 
  html += "</html>";
  server.send(200, "text/html", html);
}
