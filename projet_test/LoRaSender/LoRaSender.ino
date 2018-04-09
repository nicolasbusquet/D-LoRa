#include <SPI.h>
#include <LoRa.h> // si ce n'est déjà fait, importez la librairie LoRa via le gestionnaire de bibliothèque


/*----------------------------------------
 * Définition de la structure des messages
 */
struct __attribute__((packed)) trame_t {
      uint8_t id;
      uint8_t ts;
      char data[8];
};

/*---------------------------------------
 * INITIALISATION DU PROGRAMME
 */
void setup(){
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Emetteur LoRa");
  // initialiser le shield LoRa en 868 MHz
  LoRa.setSPIFrequency(4E6); //défaut 8MHz trop rapide pour l'analyseur
  if( !LoRa.begin(868E6) ){  //fréquence européenne 
    Serial.print("Echec de l'initialisation LoRa !\n");
    while(true); // on se bloque ici et on ne va pas plus loin
  }
}//setup()

/*--------------------------------------
 * BOUCLE DE TRAITEMENT
 */
void loop() {
  static byte N=0;
  trame_t Trame = {0};

  Serial.print("Envoi du message \"N="); Serial.print(N); Serial.println("\"");
  Trame.id = 0x30; // n° d'identification de l'émetteur
  Trame.ts = 0x00; // n° unique de message
  Trame.data[0] = 'N';
  Trame.data[1] = '=';
  Trame.data[2] = '0'+ (N/100)%10;
  Trame.data[3] = '0'+ (N/10 )%10;
  Trame.data[4] = '0'+ (N/1  )%10;
  //Trame.data[5] =
  //Trame.data[6] =
  //Trame.data[7] =
  
  //----- Début émission LoRa --------
  LoRa.beginPacket(false);
  LoRa.write( (uint8_t*)&Trame, sizeof(Trame));
  LoRa.endPacket();  
  //----- Fin émission LoRa --------
  N++;
  delay(5000);
}//loop()
