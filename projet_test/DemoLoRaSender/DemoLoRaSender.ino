#include <SPI.h>
#include <LoRa.h>

void setup(){
    Serial.begin(9600);
    while (!Serial);
    Serial.println("Emetteur LoRa");
    // initialiser le shield LoRa en 868 MHz
    if( !LoRa.begin(868E6) ){
        Serial.print("Echec de l'initialisation LoRa !\n");
        while(true); // on se bloque ici et on ne va pas plus loin
    }
}//setup()

void loop() {
    Serial.print("Envoi du message \"Equipe Prof"); Serial.println("\"");
    //----- Début émission LoRa --------
    LoRa.beginPacket();
    LoRa.print("Equipe Prof");
    LoRa.endPacket();
    //----- Fin émission LoRa --------
    delay(3000);
}//loop()
