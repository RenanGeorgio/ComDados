#include <SoftwareSerial.h>

int leitura = 0;
int estadoled = 0;
int estadoled1 = 0;

SoftwareSerial rs485(10,11);

char c=0;
int def =100;
byte d;

char t = 'T';

void setup() {
  pinMode(6, OUTPUT);       
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);     
  digitalWrite(6,LOW);      
  Serial.begin(9600);     
  rs485.begin(9600);        
  delay(60);
}
 
void loop() {

  leitura = analogRead(0);
  leitura = map(leitura,0,900,0,90);
  digitalWrite(6,LOW);
  if ( leitura >= def){
    delay(60);
    digitalWrite(12,HIGH);
    serial.print("alarme    ->");
    Serial.println(leitura);
  }
   else{
    digitalWrite(12,LOW);    
            }
  while (rs485.available()){
    c = rs485.read();
    if( c=='2'){ 
      Serial.println(c);
      digitalWrite(6,HIGH);  
      delay(60);
      rs485.write(leitura);
      Serial.println(leitura);
      rs485.flush();
      digitalWrite(6,LOW);        
      }
    if( c == '1'){ 
      Serial.println(c); 
      delay(60);
      estadoled = !estadoled; 
      if (estadoled == 0) {
        digitalWrite(13,LOW);
        Serial.println("Led 2 Desligado");
     }
      else {
        digitalWrite(13,HIGH);
        Serial.println("Led 2 Ligado");
              }            
      delay(60);
      rs485.flush();
            }
      if ( c == '5'){
        Serial.println(c);
        digitalWrite(6,HIGH);  
        delay(60);
        rs485.write('5');
        d = rs485.read(); 
        rs485.flush();
        digitalWrite(6,LOW); 
        delay(1000);
        def = rs485.parseInt();
        Serial.println(set);
      }
        delay(60);
        rs485.flush();
             }

                  
}                 
