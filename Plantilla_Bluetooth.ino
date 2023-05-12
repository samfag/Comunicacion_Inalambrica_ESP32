#include <BluetoothSerial.h>


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
       Serial.begin(9600);
       SerialBT.begin("BluetoothESP32");
}


void loop() {
             float valor1,valor2;
             if (isnan(valor1) || isnan(valor2)) {   
                return;
             }

              SerialBT.print(valor1);
              SerialBT.print(";");
              SerialBT.print(valor2);
              SerialBT.println(";");
}
