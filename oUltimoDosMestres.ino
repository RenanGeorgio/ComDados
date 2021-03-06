#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


const char* ssid = "RenanGeorgio";
const char* password = "19121992@rs";
WiFiServer server(80);

String HTTP_req; 
String URLValue;
byte byteReceived;
SoftwareSerial rs485(14, 12, false, 256);


int x=0;
char c=0;
char z=0;
int def = 0;
int i = 0;

void setup() {
  pinMode(D7,OUTPUT);
  Serial.begin(9600);
  rs485.begin(9600);
  delay(50); 

//  pinMode(D6,OUTPUT);
//  Serial.begin(9600);
//  rs485.begin(9600);
//  delay(50); 

  Serial.println(""); 
  Serial.println(""); 
  Serial.print("Conectando a "); 
  Serial.print(ssid); 

  WiFi.begin(ssid, password); 

  while (WiFi.status() != WL_CONNECTED) { 
   delay(500); 
   Serial.print("."); 
  }
  Serial.println(""); 
  Serial.print("Conectado a rede sem fio "); 
  Serial.println(ssid); 
  server.begin(); 
  Serial.println("Servidor iniciado"); 

  Serial.print("IP para se conectar ao NodeMCU: "); 
  Serial.print("http://"); 
  Serial.println(WiFi.localIP());

}
void loop(){
  WiFiClient client = server.available(); 
  if (!client) { 
   return; 
  }
  Serial.println("Novo cliente se conectou!"); 
  while(!client.available()){
   delay(1); 
  }
  String request = client.readStringUntil('\r'); 
  Serial.println(request); 
  client.flush(); 

String buf = "";
 
  buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
  buf += "<html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
  buf += "<title>ESP8266 Web Server</title>";
  buf += "<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:80%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;} .q{float: right;width: 64px;text-align: right;}</style>";
  buf += "</head>";
  buf += "<h3>ESP8266 Web Server - System Logs</h3>";
  buf += "<p>GPIO13 <a href=\"?function=led1_on\"><button>ON</button></a> <a href=\"?function=led1_off\"><button>OFF</button></a></p>";
  buf += "<p>GPIO13 <a href=\"?function=temp1_on\"><button>ON</button></a> <a href=\"?function=temp12_off\"><button>OFF</button></a></p>";
//  buf += "<p>GPIO13 <a href=\"?function=led2_on\"><button>ON</button></a> <a href=\"?function=led2_off\"><button>OFF</button></a></p>";
//  buf += "<p>GPIO13 <a href=\"?function=temp2_on\"><button>ON</button></a> <a href=\"?function=temp2_off\"><button>OFF</button></a></p>";
  buf += "</html>\n";
 
  client.print(buf);
  client.flush();
 
  if (request.indexOf("led1_on") != -1)
  {
    c = 1;
    }
    else if (request.indexOf("led1_off") != -1){
    c != 1;
  }
  else if (request.indexOf("temp1_on") != -1){
    c = 2;
  }
  else if (request.indexOf("temp2_off") != -1){
    c != 2;
  }
//  else if (request.indexOf("led2_on") != -1){
//    c =3;
//  }
    
//  else if (req.indexOf("led4_off") != -1)
//    digitalWrite(4, 0);
  else {
    Serial.println("invalid request");
    client.stop();
  }
  Serial.println("Client disonnected");


//  client.println("<head><meta http-equiv='refresh' content='4'></head>");
//  client.println("HTTP/1.1 200 OK"); 
//  client.println("Content-Type: text/html"); 
//  client.println("");
//  client.println("<!DOCTYPE HTML>"); 
//  client.println("<html>"); 
//  client.println("<head><meta http-equiv='refresh' content='4'></head>");
//  client.println("<h1><center>Ola cliente!</center></h1>"); 
//  client.println("<center><font size='5'>Seja bem vindo!</center>"); 
//  client.println("</html>"); 
//  delay(1); 
//  Serial.println("Cliente desconectado");
//  Serial.println(""); 
  
  

while(Serial.available())
  {
   i = 0;
   c = Serial.read(); 

   if (c == '2' || c == '1'){
     Serial.println("digite um comando: (1) Acionar o atuador escravo 1 \n (2) Temperatura escravo 1 \n (3) Acionar o atuador escravo 2 \n (4) Temperatura escravo 2 \n (5) Definir Setpoint escravo 1 \n (6) Definir Setpoint escravo 2 \n\n");  
     digitalWrite(D7, HIGH);
     delay(200);
     rs485.write(c);
     Serial.print("                 Comando executado:");
     Serial.println(c);
     Serial.print("\n");
     digitalWrite(D7, LOW);
     delay(150);
 
    

     while(rs485.available()){
      x = rs485.read(); 
      z = rs485.read();
      rs485.flush();
      Serial.print("                 Temperatura do sensor 1:"); 
      Serial.println(x);
      z = rs485.read(); 
      delay(400);
    }
   }

    if (c == '3' || c == '4'){
     Serial.println("digite um comando: (1) Acionar o atuador escravo 1 \n (2) Temperatura escravo 1 \n (3) Acionar o atuador escravo 2 \n (4) Temperatura escravo 2 \n (5) Definir Setpoint escravo 1 \n (6) Definir Setpoint escravo 2 \n\n");  
     digitalWrite(D6, HIGH);
     delay(200);
     rs485.write(c);
     Serial.print("                 Comando executado:");
     Serial.println(c);
     Serial.print("\n");
     digitalWrite(D6, LOW);
     delay(150);
  

     while(rs485.available()){
      x = rs485.read(); 
      z = rs485.read();
      rs485.flush();
      Serial.print("                 Temperatura do sensor 2:"); 
      Serial.println(x);
      z = rs485.read(); 
      delay(400);
    }
    }

   if ( c == '5') { 
    Serial.println("digite um comando: (1) Acionar o atuador escravo 1 \n (2) Temperatura escravo 1 \n (3) Acionar o atuador escravo 2 \n (4) Temperatura escravo 2 \n (5) Definir Setpoint escravo 1 \n (6) Definir Setpoint escravo 2 \n\n");  
    delay(200);
    digitalWrite(D7, HIGH);
    rs485.write(c);
    Serial.print("                   Comando executado:");
    Serial.println(c);
    Serial.print("\n");
    Serial.print("   Digite um Setpoint para o escravo 1: \n`");
    delay(50);
    digitalWrite(D7, LOW);
    z = rs485.read(); 
    delay(1000);

    if(Serial.available()){
     def = Serial.parseInt();
     Serial.print("                    Setpoint escravo 1:");
     digitalWrite(D7, HIGH);
     rs485.print(def);
     digitalWrite(D7, LOW);
     z = rs485.read(); 
     delay(100);
     Serial.println(def);
     Serial.print("\n");}
    }
    
     if ( c == '6') { 
    Serial.println("digite um comando: (1) Acionar o atuador escravo 1 \n (2) Temperatura escravo 1 \n (3) Acionar o atuador escravo 2 \n (4) Temperatura escravo 2 \n (5) Definir Setpoint escravo 1 \n (6) Definir Setpoint escravo 2 \n\n");  
    delay(200);
    digitalWrite(D6, HIGH);
    rs485.write(c);
    Serial.print("                   Comando executado:");
    Serial.println(c);
    Serial.print("\n");
    Serial.print("   Digite um Setpoint do escravo 2: \n`");
    delay(50);
    digitalWrite(D6, LOW);
    z = rs485.read(); 
    delay(1000);

    if(Serial.available()){
     def = Serial.parseInt();
     Serial.print("                    Setpoint escravo 2:");
     digitalWrite(D6, HIGH);
     rs485.print(def);
     digitalWrite(D6, LOW);
     z = rs485.read(); 
     delay(100);
     Serial.println(def);
     Serial.print("\n");}
    }
    }    
}

  

    
