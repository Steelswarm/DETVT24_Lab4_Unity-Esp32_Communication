//=====================
//HTML code for webpage
//=====================
const char webpageCode[] PROGMEM =
R"=====(
<!DOCTYPE HTML>
<html>
<head>
  <title>ESP32 Web Server</title>
</head>
<!-------------------------------C S S------------------------------>
<style>
  #btn
  {
    display: inline-block;
    text-decoration: none;
    background: #8CD460;
    color: rgba(255,255,255, 0.80);
    font-weight: bold;
    font: 60px arial, sans-serif;
    width: 150px;
    height: 150px;
    line-height: 150px;
    border-radius: 50%;
    text-align: center;
    vertical-align: middle;
    overflow: hidden;
    box-shadow: 0px 0px 0px 8px #8CD460;
    border: solid 2px rgba(255,255,255, 0.47);
    transition: 0.5s;
  }
  #btn2
  {
    display: inline-block;
    text-decoration: none;
    background: #8CD460;
    color: rgba(255,255,255, 0.80);
    font-weight: bold;
    font: 60px arial, sans-serif;
    width: 150px;
    height: 150px;
    line-height: 150px;
    border-radius: 50%;
    text-align: center;
    vertical-align: middle;
    overflow: hidden;
    box-shadow: 0px 0px 0px 8px #8CD460;
    border: solid 2px rgba(255,255,255, 0.47);
    transition: 0.5s;
  }
  body {text-align:center; font-family:"Calibri"; background-color:rgba(0, 3, 8, 0.26)}
  h1   {color: rgba(0, 0, 255, 0.87); font-size: 50px;}
</style>
<!------------------------------H T M L----------------------------->
<body>
   <h1>E S P 3 2<br>WebSocket Server</h1>
   <a href="#" id="btn" ONCLICK='button()'> </a>
   <a href="#" id="btn2" ONCLICK='button2()'> </a>
<!-----------------------------JavaScript--------------------------->
  <script>
     InitWebSocket()
     function InitWebSocket()
     {
       websock = new WebSocket('ws://'+window.location.hostname+':81/'); 
       websock.onmessage = function(evt)
       {
          JSONobj = JSON.parse(evt.data);
          document.getElementById('btn').innerHTML = JSONobj.LEDonoff;
          if(JSONobj.LEDonoff == 'ON')
          {
            document.getElementById('btn').style.background='#FF0000';
            document.getElementById('btn').style["boxShadow"] = "0px 0px 0px 8px #FF0000";
          }
          else
          {
            document.getElementById('btn').style.background='#111111';
            document.getElementById('btn').style["boxShadow"] = "0px 0px 0px 8px #111111";
          }
       }
     }
     //-------------------------------------------------------------
     function button()
     {
        btn = 'LEDonoff=ON';
        if(document.getElementById('btn').innerHTML == 'ON')
        {
          btn = 'LEDonoff=OFF';
        }
        websock.send(btn);
     }

      function button2()
     {
        message = 'message=test';
        websock.send(message);
     }
  </script>
</body>
</html>
)====="; 