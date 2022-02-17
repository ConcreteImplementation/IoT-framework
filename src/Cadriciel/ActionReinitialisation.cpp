#include "Cadriciel/ActionReinitialisation.h"

#include <WiFiManager.h>

ActionReinitialisation::ActionReinitialisation() 
{ ; }


void ActionReinitialisation::executer() {
#if EST_DEBUG 
	Serial.println("\n***Reinitialisation***\n");
	delay(1000);
#endif

	WiFiManager wifiManager;
	wifiManager.erase();         // Pour effacer le réseau sauvegardé
	wifiManager.resetSettings(); // Pour effacer les parametres utilisateurs

	ESP.restart();
}