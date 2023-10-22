const char reb_d[] = R"rawliteral(
   function rebootdev() {
        modal.style.display = "block";
     }
   var t = 60;
   var time = document.getElementsByClassName("clock")[0];
     function fun() {
         t--;
        time.innerHTML = "<b>Оставшееся время: "+ t +" сек.</b>"
       if(t <= 0) {
         location.href = "/";
         clearInterval(inter);
       }
   }
   
  function rebootdev_s() {
      var msg = document.getElementsByClassName("modal-body")[0];
      var req5 = new XMLHttpRequest();
            req5.open('GET','/?page=dev_reboot');
            req5.onreadystatechange = function(){
              if (req5.readyState === 4 && req5.status === 200) {
                     msg.innerHTML ="<br><b>Выполняется перезапуск устройства...</b><br>"
                     var inter = setInterval("fun()", 1000);
              }
            }
        req5.send();
})rawliteral";

//=========================================

const char html[] = R"(
                  body {
                  background: linear-gradient(to bottom, #060345, #023f78, #540110, #013a42, #1f3d6e);
                    }
                  form {
                       margin: 20px auto 0;
                       max-width: 500px;
                       padding: 10px;
                       border-radius: 10px;
                       background-color: #fff;
                    }
                  div#response2, div#response21 {
                       margin: 10px auto 0;
                       max-width: 500px;
                       padding: 20px;
                       border-radius: 10px;
                       background: linear-gradient(to bottom right, #9df3f5, #e6e8e7);
                    }
                    label {
                        display: block;
                        color: #5769a1;
                        margin: 10px;
                    }
                  input[type=text], input[type=password], input[type=number], input[type=file], select {
                        width: 100%;
                        padding: 10px;
                        margin-bottom: 15px;
                        border: 1px solid #ccc;
                        border-radius: 4px;
                        box-sizing: border-box;
                      }
                     input[type=submit] {
                        background-color: #3482f7;
                        color: white;
                        padding: 12px 20px;
                        border: none;
                        border-radius: 4px;
                        cursor: pointer;
                     }
                    h2 {
                        text-align: center;
                        margin-top: 10px;
                        font-size: 30px;
                        color: white;
                    }
                    text {
                       text-align: left;
                       margin-top: 5px;
                       font-size: 15px;
                       font-family: Arial;
                       color: #01302b;
                     }
                    div.live {
                       text-align: right;
                       margin-top: 0px;
                       font-size: 30px;
                       font-family: Arial;
                       color: #066094;
                     }
                     div.livePM {
                       text-align: right;
                       margin-top: 0px;
                       font-size: 35px;
                       font-family: Monotype Corsiva;
                       color: #800404;
                     }
                    div.modal {
                       text-align: left;
                       margin-top: 0px;
                       font-size: 30px;
                       color: #066094;
                     }
                      a {
                       text-align: center;
                       margin-top: 0px;
                       font-size: 16px;
                       text-decoration: none;
                       color: #9ee8e8;
                     }
                     a.mod {
                       text-align: center;
                       margin-top: 0px;
                       font-size: 18px;
                       text-decoration: none;
                       color: #3e5d80;
                     }
                    .spoiler input, .spoiler div  { 
                        display: none; 
                     }
                    .spoiler :checked ~ div {
                     display: block;
                     }
                     footer {
                       text-align: center;
                       margin-top: 10px;
                       font-size: 15px;
                       color: #cbd6f2;
                     }
                      #myBtn {                     
                      background-color: #9C27B0;  
                      color: white; 
                      padding: 12px 16px;
                      font-size: 18px;   
                      font-weight: bold;   
                      border: none;   
                      cursor: pointer;   
                      width: 180px;        
                     }                          
                      .modal {
                        display: none; /* Hidden by default */
                        position: fixed; /* Stay in place */
                        z-index: 1; /* Sit on top */
                        padding-top: 250px; /* Location of the box */
                        left: 0;
                        top: 0;
                        width: 100%; /* Full width */
                        height: 100%; /* Full height */
                        overflow: auto; /* Enable scroll if needed */
                        background-color: rgb(0,0,0); /* Fallback color */
                        background-color: rgba(0,0,0,0.4); /* Black w/ opacity */
                        border-radius: 10px;
                    }
                    .modal-content {
                        position: relative;
                        background-color: #97e1f7;
                        margin: auto;
                        padding: 0;
                        border: 0px solid #cdeef7;
                        width: fit-content;
                        border-radius: 10px;
                        box-shadow: 0 4px 8px 0 rgba(0,0,0,0.2),0 6px 20px 0 rgba(0,0,0,0.19);
                        -webkit-animation-name: animatetop;
                        -webkit-animation-duration: 0.4s;
                        animation-name: animatetop;
                        animation-duration: 0.4s;
                    }
                   @-webkit-keyframes animatetop {
                        from {top:-300px; opacity:0}
                        to {top:0; opacity:1}
                    }
                   @keyframes animatetop {
                        from {top:-300px; opacity:0}
                        to {top:0; opacity:1}
                    }
                     .close {
                        color: white;
                        float: right;
                        font-size: 28px;
                        font-weight: bold;
                    }
                    .close:hover,
                    .close:focus {
                        color: #000;
                        text-decoration: none;
                        cursor: pointer;
                    }
                    .modal-header {
                        padding: 5px 16px;
                        color: white;
                        font-size: 12px;
                        text-align: left;
                        border-radius: 10px;
                    }
                    .modal-body {
                        padding: 12px 16px;
                        font-size: 18px;
                        text-align: center;
                    }
                    .modal-footer {
                        padding: 12px 16px;
                        color: #702457;
                        font-size: 16px;
                        text-align: right;
                        border-radius: 10px;
                    }
                    .input-file {
                    position: relative;
                    display: inline-block;
                    padding: 10px 20px;
                    border: none;
                    border-radius: 4px;
                    }
                   .input-file span {
                   position: relative;
                   display: inline-block;
                   cursor: pointer;
                   outline: none;
                   text-decoration: none;
                   font-size: 14px;
                   vertical-align: middle;
                   color: rgb(255 255 255);
                   text-align: center;
                   border-radius: 4px;
                   background-color: #419152;
                   line-height: 22px;
                   height: 40px;
                   padding: 10px 20px;
                   box-sizing: border-box;
                   border: none;
                   margin: 0;
                   transition: background-color 0.2s;
                  }
                  .input-file input[type=file] {
                   position: absolute;
                   margin: 10;
                   z-index: -1;
                   opacity: 0;
                   display: block;
                    width: 0;
                   height: 0;
                    }
 
                  /* Focus */
                  .input-file input[type=file]:focus + span {
                   box-shadow: 0 0 0 0.2rem rgba(0,123,255,.25);
                    }
 
                  /* Hover/active */
                  .input-file:hover span {
                  background-color: #59be6e;
                   }
                  .input-file:active span {
                  background-color: #2E703A;
                    }
 
                  /* Disabled */
                  .input-file input[type=file]:disabled + span {
                    background-color: #eee;
                  })";

//================================================
const char divcode[] = R"rawliteral(
    <div id="myModal" class="modal">
  <div class="modal-content">
    <div class="modal-header">
      <span class="close">&times;</span>
      <text>Перезагрузка устройства</text>
    </div>
    <div class="modal-body">
     <br>
      <a class ="mod" href="javascript:void(0)" onclick="rebootdev_s()"><b>Нажмите для перезагрузки устройства</b></a>
      <br>
    </div>
    <div class="modal-footer">
      <span class = "clock"> <br></span>
    </div>
  </div>
</div>
 <script>
 var modal = document.getElementById("myModal");
 var span = document.getElementsByClassName('close')[0];
 span.onclick = function() {
     modal.style.display = "none";
 }
  window.onclick = function(event) {
     if(event.target == modal) {
         modal.style.display = "none";
     }
   }
  </script>)rawliteral";
  
 //==============================================
 // Скрипт для формы конфигурации
const char config_js[] = R"rawliteral(
  <script>
        const form = document.getElementById('config-form');
              form.addEventListener('submit', (event) => {
                    event.preventDefault();
                    const formData = new FormData(form);
                    const xhr = new XMLHttpRequest(); 
                          xhr.open('POST', '/?page=indata');  
                          xhr.addEventListener('load', () => {
                           if (xhr.status === 200) {
                                  document.getElementById('response').innerHTML = xhr.responseText;
                                    }else{
                                       document.getElementById('response').innerHTML = 'Ошибка отправки';
                                          }
                                    });
                          xhr.send(formData);
                       });
   </script>
   <script>
          document.getElementById('switch').addEventListener('change', function() {
                  var status = this.checked ? 'on' : 'off';
                  var xhr = new XMLHttpRequest();
                  xhr.open('POST', '?page=indata', true);
                  xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
                  xhr.onreadystatechange = function() {
                   if (this.readyState === XMLHttpRequest.DONE && this.status === 200) {
                          document.getElementById('response2').innerHTML = xhr.responseText;
                        }
                    };
                  xhr.send('switch=' + status);
                });
  </script>)rawliteral";
 //========================================
 //JS смены пароля
 const char pass_js[] = R"rawliteral(
  <script>
       const form = document.getElementById('config-form');
             form.addEventListener('submit', (event) => {
                  event.preventDefault();
                  const formData = new FormData(form);
                  const xhr = new XMLHttpRequest();
                        xhr.open('POST', '?page=indata');
                        xhr.addEventListener('load', () => {
                              if (xhr.status === 200) { 
                                    document.getElementById('response').innerHTML = xhr.responseText; 
                                   }else{
                                    document.getElementById('response').innerHTML = 'Ошибка отправки';
                                 }
                            });
                   var newPassword = document.getElementById("password").value;
                   var confirmNewPassword = document.getElementById("newpassword").value;
                      if (newPassword != confirmNewPassword) {
                               document.getElementById('response').innerHTML = 'Пароли не совпадают!';
                               return false;
                             }else{
                               xhr.send(formData);
                              }
                          });
  </script>)rawliteral";
  //====================================
  //Update js
  const char update_js[] = R"rawliteral(
    <script>
         const form = document.getElementById('config-form');
               form.addEventListener('submit', (event) => {
               event.preventDefault();
               const formData = new FormData(form);
               const xhr = new XMLHttpRequest();
                     xhr.open('POST', '/update');
                     xhr.addEventListener('load', () => {
                  if (xhr.status === 200) {
                         document.getElementById('response').innerHTML = xhr.responseText.replace('Update Success! Rebooting...','<text>Обновление выполнено успешно! Выполняется перезагрузка устройства, подождите...</text>'); 
                      }else{
                         document.getElementById('response').innerHTML = '<text>Ошибка отправки</text>'; 
                       }
               });
                     document.getElementById('response').innerHTML = '<text>Выполняется процесс обновления прошивки... Пожалуйста, не покидайте страницу в процессе обновления!</text>';
                     xhr.send(formData);
            });
   </script>)rawliteral";
//==============================================
const char js[] = R"rawliteral(
       <script>
       setInterval(server_time, 1000);
      function server_time(){
         var worktime = new XMLHttpRequest();
             worktime.open("GET","?page=time",true);
             worktime.onreadystatechange = function(){
          if (worktime.readyState === 4 && worktime.status === 200) {
                const obj = JSON.parse(worktime.responseText);
                document.getElementById("timew").innerHTML  = obj.time;
                document.getElementById("CP10s").innerHTML  = obj.CP10s;
                document.getElementById("CP1m").innerHTML   = obj.CP1m;
                document.getElementById("CP5m").innerHTML   = obj.CP5m;
                document.getElementById("CP60m").innerHTML  = obj.CP60m;
                document.getElementById("val10s").innerHTML = obj.val10s;
                document.getElementById("val1m").innerHTML  = obj.val1m;
                document.getElementById("MQTT").innerHTML   = obj.MQTT;
                document.getElementById("val5m").innerHTML  = obj.val5m;  
                document.getElementById("val60m").innerHTML = obj.val60m;
                document.getElementById("PM").innerHTML     = obj.PM;
                }
              }
             worktime.send();
           }
          </script>)rawliteral";
