void update_fw_page(){
 if (!validateToken()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  httpUpdater.setup(&server);
  String html  = "<html><head><meta charset=\"UTF-8\"><title>Обновление прошивки</title>";
         html += "<link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\" />";
         html += "</head><body>";
         html += "<h2>Обновление прошивки устройства</h2>";
         html += "<form id=\"config-form\" enctype=\"multipart/form-data\" >";
         html += "<div id=\"response\">";
         html += "<label for=\"file\">Файл прошивки:</label>";
         html += "<label class=\"input-file\">";
         html += "<input type=\"file\" id=\"file\" accept=\".bin,.bin.gz\" name=\"firmware\" required>";
         html += "  <span>Выберите файл</span>";
         html += "</label>";
         html += "<input type=\"submit\" value=\"Обновить прошивку\">";
         html += "</div>";
         html += "</form><br>";
         html += "<center><br><a href=\"/\">Вернуться назад</a><br></center>";
         html += "<footer>© <b>CYBEREX TECH</b>, 2023. Версия микро ПО <b>"+version_code+"</b>.</footer></html>";
         html += update_js;
         html += "</body></html>";
  server.send(200, "text/html", html);
}
