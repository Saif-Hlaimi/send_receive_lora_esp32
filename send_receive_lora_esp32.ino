#include <SPI.h>
#include <LoRa.h>
#include <stdlib.h>

//************** declaration of LoRa Pins *************************
#define ss 15
#define rst 4
#define dio0 5
//****************************************************************

// Tracks the time since last event fired
//***************************decalaration of variables**********************
unsigned long currentMillis;
unsigned long previousMillis = 0;
const long sendInterval = 4000; // 4 seconds
const long receiveInterval = 4000; // 4 seconds
bool sendMode = true;
String ch="hello from ESP";
//***************************************************************************


void setup() {


  // put your setup code here, to run once:
  Serial.begin(921600);
   Serial.println("Initializing...");
  while (!Serial);



//***********Inintialisation de LoRa***********************
  Serial.println("LoRa Principale");
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
  LoRa.setTxPower(20);
//********************************************************


}

void loop() {
  // put your main code here, to run repeatedly:

  currentMillis = millis();
  if (sendMode && currentMillis - previousMillis >= sendInterval) {
    previousMillis = currentMillis;
    sendMode = false;
  } else if (!sendMode && currentMillis - previousMillis >= receiveInterval) {
    previousMillis = currentMillis;
    sendMode = true;
  }
  
  if (sendMode) {
    // Send data
    
      SendMessage(ch);
    }
    else  {
      onReceive(LoRa.parsePacket());
    }
}


void SendMessage(String data)
{ 
  Serial.print(" sending data: ");
  Serial.println(data);
  LoRa.beginPacket();
  LoRa.println(data);
  LoRa.endPacket();

 
}

void onReceive (int packetSize){

  String data = LoRa.readString();


  if (packetSize == 0) {
    Serial.println(" there is no data received ! ");
    return;
  } else {
       Serial.print("received data : ");
  Serial.println(data);
  }

}
