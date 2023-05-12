
#include <Ubidots.h>

const char* UBIDOTS_TOKEN = "";
const char* WIFI_SSID = ""; 
const char* WIFI_PASS = ""; 



Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

void setup() {
  Serial.begin(9600);  
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS); 
}

void loop() {
  ubidots.add("Parametro1", sensor1);  
  ubidots.add("Parametro2", sensor2); 
  ubidots.send();
  delay(2000);
}
