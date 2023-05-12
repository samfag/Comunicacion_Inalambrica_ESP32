#include <DHT11.h>
#include <BluetoothSerial.h>

int pin=25;
DHT11 dht11(pin);

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup()
   {
       Serial.begin(9600);
       SerialBT.begin("BluetoothESP32");
   }

void loop()
   {
       int err;
       float temp, hum;
       if((err = dht11.read(hum, temp)) == 0)    // Si devuelve 0 es que ha leido bien
          {
             Serial.print("Temperatura: ");
             Serial.print(temp);
             Serial.print(" Humedad: ");
             Serial.print(hum);
             Serial.println();

             if (isnan(temp) || isnan(hum)) {
                return;
             }

              SerialBT.print(temp);
              SerialBT.print(";");
              SerialBT.print(hum);
              SerialBT.println(";");
          }
       else
          {
             Serial.println();
             Serial.print("Error Num :");
             Serial.print(err);
             Serial.println();
          }
       delay(1000);            //Recordad que solo lee una vez por segundo
   }
