

#include <Ubidots.h>

  const char* UBIDOTS_TOKEN = "BBFF-IoSacxhn7pnTG0jU9Wlw7WuFozMZ7C"; //Ubidots TOKEN
  const char* WIFI_SSID = "IZZI-6CC1"; // SSID de Wi-Fi
  const char* WIFI_PASS = "704FB8416CC1"; //contraseña de Wi-Fi
  
  float tempC; // Variable para almacenar el valor obtenido del sensor (0 a 1023)
  int pinLM35 = 34; // Variable del pin de entrada del sensor (GPIO34)
  
  #define PIN_TRIG 2
  #define PIN_ECHO 15
  
  float tiempo;
  float distancia;
  
  Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

void setup() {
   Serial.begin(9600);   //Se inicia la comunicación serial 
   ubidots.wifiConnect(WIFI_SSID, WIFI_PASS); 
   pinMode(PIN_TRIG, OUTPUT);
   pinMode(PIN_ECHO, INPUT);
}

void loop() {

  // Con analogRead leemos el sensor, recuerda que es un valor de 0 a 1023
  tempC = analogRead(pinLM35); 
   
  // Calculamos la temperatura con la fórmula
  tempC = (5.0 * tempC * 100.0)/1024.0 - 30.0; 
 
  // Envia el dato al puerto serial
  Serial.print(tempC);
  // Salto de línea
  Serial.print("\n");
  
  // Esperamos un tiempo para repetir el loop
  delay(1000);

  digitalWrite(PIN_TRIG, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
   
  digitalWrite(PIN_TRIG, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
   
  tiempo = pulseIn(PIN_ECHO, HIGH);
  distancia = tiempo/58.3;

  Serial.println(distancia);

  delay(1000);
   
  ubidots.add("temperatura", tempC);  
  ubidots.add("distancia", distancia); 

  ubidots.send();
  delay(2000);

}
