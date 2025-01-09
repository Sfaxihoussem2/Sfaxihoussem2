#include <WiegandMulti.h>
#include <Arduino.h>

WIEGANDMULTI wg;
WIEGANDMULTI wg2;
String CardNumber = "008918875"; // Note: Use the card number as a string

void Reader1D0Interrupt(void)
{
  wg.ReadD0();
}

void Reader1D1Interrupt(void)
{
  wg.ReadD1();
}

void Reader2D0Interrupt(void)
{
  wg2.ReadD0();
}

void Reader2D1Interrupt(void)
{
  wg2.ReadD1();
}


void setup() {
	Serial.begin(9600);  
	wg.begin(2,4,Reader1D0Interrupt,Reader1D1Interrupt);
	wg2.begin(34,35,Reader2D0Interrupt,Reader2D1Interrupt);
   Serial.println("Bring your Wiegand Card Closer...");
}

void loop() {
	  if (wg.available()) {
    unsigned long decimalCode = wg.getCode();  // Obtenez le code décimal de WG1
    handleCardAccess(decimalCode);
  } else if (wg2.available()) {
    unsigned long decimalCode = wg2.getCode();  // Obtenez le code décimal de WG2
    handleCardAccess(decimalCode);
  }
}

void handleCardAccess(unsigned long decimalCode) {
  String cardID = String(decimalCode);       // Convertissez le code décimal en une chaîne de caractères
  while (cardID.length() < 11) {
    cardID = "0" + cardID;
  }
  Serial.println(cardID);
  Serial.println("ID de la carte : " + cardID);
  Serial.println("ID d'accès : " + CardNumber);

  if (cardID == CardNumber) {
    Serial.println("Accès autorisé");
    digitalWrite(15, LOW);  // Allume la LED (LOW est le niveau de tension)
  } else {
    Serial.println("Accès refusé");
    digitalWrite(15, HIGH);  // Éteint la LED (HIGH est le niveau de tension)
  }

  Serial.println(" ");
  Serial.println("Approchez votre carte RFID...");
}