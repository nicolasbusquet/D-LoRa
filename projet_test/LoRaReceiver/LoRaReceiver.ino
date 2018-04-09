#include <SPI.h>
#include <LoRa.h>
#include "util.h" // pour avoir l'affichage du temps écoulé

#define LENMAX 80 // taille maximale acceptée pour la trame

// void setSPIFrequency(uint32_t frequency); // 8MHz par défaut c'est bq pour l'analyseur logique

void setup(){
  Serial.begin(9600);
  while (!Serial);
  Serial.print("Recepteur LoRa\n");
  // initialiser le shield LoRa en 868 MHz
  if( !LoRa.begin(868E6) ){
    Serial.print("Echec de l'initialisation LoRa !\n");
    while(true); // on se bloque ici et on ne va pas plus loin
  }
}//setup()

void loop() {
    static byte tampon[LENMAX]={0};
    int longueurTrame;
    // si le module a reçu une trame alors sa longueur sera non nulle
    longueurTrame=LoRa.parsePacket();
    if( longueurTrame > 0 ){
        //---- copie de la trame depuis le modem vers le tampon ----
        if( longueurTrame>LENMAX ){
            Serial.print("Trame reçue est trop grande pour le tampon : ");
            Serial.println(longueurTrame);
            longueurTrame=LENMAX; // troncature
        }
        for( int i=0; i<longueurTrame; i++ ){
            tampon[i]=(byte)LoRa.read();
        }
        //---- affichage de l'heure d'arrivée ----
        SerialPrintElapsedTime();
        //---- affichage en hexadécimal ----
        Serial.print("0x");
        for( int i=0; i<longueurTrame; i++ ){
            if( tampon[i] < 0x0F ) Serial.print("0");
            Serial.print( tampon[i], HEX );
        }
        //---- affichage en ASCII ----
        Serial.print( " " );
        for( int i=0; i<longueurTrame; i++ ){
            if( (tampon[i] < 0x20)||(tampon[i] > 0x7E) ){
                Serial.print( "."); // ce caractère est non imprimable
            }else{
                Serial.print( (char)tampon[i] );
            }
        }
        Serial.print( "\n" );
    }//if LoRa.parsePacket
    delay(100);
}//loop()




