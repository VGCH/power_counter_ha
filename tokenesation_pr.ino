// Функция проверки существования токена
bool validateToken() {
    bool stat = false;
    if (server.hasHeader("Cookie")) {
           String cookie = server.header("Cookie")+"";    // Извлекаем токен из заголовков 
           cookie.replace("SESSIONID=", "");
           long now = millis() / 1000;

       for (int i = 0; i < 100; i++) {
           if (cookie == tokens[i].value) {
              long tokenAge = now - tokens[i].created;
                 if (tokenAge > tokens[i].lifetime) {
                       tokens[i].value = "";
                       stat = false;                      // токен истек
                     }else{
                       stat = true;                       // токен действителен
                     }
                 }
             }
         }
      return stat;
  }

// Функция генерации токена
String generateToken() {
     static const char alphanum[] =                      // Набор символов из которых будет ренерироваться токен
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

     String tokenValue = "";
         for (int i = 0; i < 5; ++i) {
               tokenValue += alphanum[random(sizeof(alphanum))];
           }
      return tokenValue;
}
