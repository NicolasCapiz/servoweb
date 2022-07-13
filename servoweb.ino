#include <WiFi.h>
#include <Servo.h>

Servo myservo[6];
static const int servoPin[6] = {13, 12, 14, 27,33,32};
String valueString = String(5);
int pos1 = 0;
int pos2 = 0;
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

const char* ssid     = "wifiNico"; // Nombre de la red 
const char* password = "12345678";     // Contraseña

WiFiServer server(80);
String header;

void setup() {
  Serial.begin(9600);
  myservo[0].attach(servoPin[0]);
  myservo[1].attach(servoPin[1]);
  myservo[2].attach(servoPin[2]);
  myservo[3].attach(servoPin[3]);
  myservo[4].attach(servoPin[4]);
  myservo[5].attach(servoPin[5]);

//  myservo2.attach(servoPin2);

  // Conectarse a la red wifi con ssid y pass
  Serial.print("Setting AP (Access Point)…");
  // 
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin(); // Inicia el servidor
}

void loop(){
  WiFiClient client = server.available();   // Escucha los clientes entrantes

  if (client) {        
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("Nuevo Cliente.");       //Imprime mensaje
    String currentLine = "";                // Cadena para contener los datos del cliente entrantes
    while (client.connected() && currentTime - previousTime <= timeoutTime) {            // Bucle cuando el cliente esta conectado
      currentTime = millis();
      if (client.available()) {
        char c = client.read();             // lee byte
        Serial.write(c);                    // lo imprime 
        header += c;
        if (c == '\n') {                    // si el byte es un caracter de nueva linea
          // si la línea actual está en blanco, tienes dos caracteres de nueva línea seguidos.
          // final de la solicitud HTTP,envia respuesta:
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto;}");
            client.println(".slider { width: 300px; }</style>");
            client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
                     
            // Web Page
            client.println("</head><body><h1>ESP32 with Servo</h1>");

            //ServoA slide bar
            client.println("<p>Servo PosA: <span id=\"servoPosA\"></span></p>");          
            client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSliderA\" onchange=\"servo(this.value,'A')\" value=\""+valueString+"\"/>");
            //ServoB slide bar
            client.println("<p>Servo PosB: <span id=\"servoPosB\"></span></p>");          
            client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSliderB\" onchange=\"servo(this.value,'B')\" value=\""+valueString+"\"/>");
            //ServoC slide bar
            client.println("<p>Servo PosC: <span id=\"servoPosC\"></span></p>");          
            client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSliderC\" onchange=\"servo(this.value,'C')\" value=\""+valueString+"\"/>");
            //ServoD slide bar
            client.println("<p>Servo PosD: <span id=\"servoPosD\"></span></p>");          
            client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSliderD\" onchange=\"servo(this.value,'D')\" value=\""+valueString+"\"/>");
            //ServoE slide bar
            client.println("<p>Servo PosE: <span id=\"servoPosE\"></span></p>");          
            client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSliderE\" onchange=\"servo(this.value,'E')\" value=\""+valueString+"\"/>");
            //ServoF slide bar
            client.println("<p>Servo PosF: <span id=\"servoPosF\"></span></p>");          
            client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSliderF\" onchange=\"servo(this.value,'F')\" value=\""+valueString+"\"/>");
            
            client.println("<script>");
             //send A value
            client.println("var sliderA = document.getElementById(\"servoSliderA\");");
            client.println("var servoPA = document.getElementById(\"servoPosA\"); servoPA.innerHTML = sliderA.value;");
            client.println("sliderA.oninput = function() { sliderA.value = this.value; servoPA.innerHTML = this.value; }");

            //send B value
            client.println("var sliderB = document.getElementById(\"servoSliderB\");");
            client.println("var servoPB = document.getElementById(\"servoPosB\"); servoPB.innerHTML = sliderB.value;");
            client.println("sliderB.oninput = function() { sliderB.value = this.value; servoPB.innerHTML = this.value; }");

            //send C value
            client.println("var sliderC = document.getElementById(\"servoSliderC\");");
            client.println("var servoPC = document.getElementById(\"servoPosC\"); servoPC.innerHTML = sliderC.value;");
            client.println("sliderC.oninput = function() { sliderC.value = this.value; servoPC.innerHTML = this.value; }");

            //send D value
            client.println("var sliderD = document.getElementById(\"servoSliderD\");");
            client.println("var servoPD = document.getElementById(\"servoPosD\"); servoPD.innerHTML = sliderD.value;");
            client.println("sliderD.oninput = function() { sliderD.value = this.value; servoPD.innerHTML = this.value; }");

            //send E value
            client.println("var sliderE = document.getElementById(\"servoSliderE\");");
            client.println("var servoPE = document.getElementById(\"servoPosE\"); servoPE.innerHTML = sliderE.value;");
            client.println("sliderE.oninput = function() { sliderE.value = this.value; servoPE.innerHTML = this.value; }");

            //send F value
            client.println("var sliderF = document.getElementById(\"servoSliderF\");");
            client.println("var servoPF = document.getElementById(\"servoPosF\"); servoPF.innerHTML = sliderF.value;");
            client.println("sliderF.oninput = function() { sliderF.value = this.value; servoPF.innerHTML = this.value; }");

            
            client.println("$.ajaxSetup({timeout:1000}); function servo(pos,color) { ");
            client.println("$.get(\"/?value\" + color + \"=\" + pos + \"&\"); {Connection: close};}</script>");
           
            client.println("</body></html>");   
            
             //GET /?value=180& HTTP/1.1
             if(header.indexOf("GET /?valueA=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1+1, pos2);

              //ServoをvalueStringの値で点灯
              myservo[0].write(valueString.toInt());
              Serial.println(valueString); 
            }  
            //ServoBの値をServoの出力に変換
            if(header.indexOf("GET /?valueB=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1+1, pos2);

              //ServoをvalueStringの値で点灯
              myservo[1].write(valueString.toInt());
              Serial.println(valueString); 
            }  

            //ServoCの値をServoの出力に変換
            if(header.indexOf("GET /?valueC=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1+1, pos2);

              //ServoをvalueStringの値で点灯
              myservo[2].write(valueString.toInt());
              Serial.println(valueString); 
            }

            //ServoDの値をServoの出力に変換
            if(header.indexOf("GET /?valueD=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1+1, pos2);

              //ServoをvalueStringの値で点灯
              myservo[3].write(valueString.toInt());
              Serial.println(valueString); 
            }

            //ServoEの値をServoの出力に変換
            if(header.indexOf("GET /?valueE=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1+1, pos2);

              //ServoをvalueStringの値で点灯
              myservo[4].write(valueString.toInt());
              Serial.println(valueString); 
            }

            //ServoFの値をServoの出力に変換
            if(header.indexOf("GET /?valueF=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1+1, pos2);

              //ServoをvalueStringの値で点灯
              myservo[5].write(valueString.toInt());
              Serial.println(valueString); 
            }
            client.println();
            // Break out of the while loop
            break;
          } else { // Si tiene nueva linea que borre
            currentLine = "";
          }
        } else if (c != '\r') {  // si obtuvo algo mas,
          currentLine += c;      // agregarlo al currenLine
        }
      }
    }
    // limpiar
    header = "";
    // Cierra la conexion
    client.stop();
    Serial.println("Cliente desconectado.");
    Serial.println("");
  }
}
