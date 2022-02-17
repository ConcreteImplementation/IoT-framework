#include "Observeurs/MQTT/PublisherMQTT.h"

#define BASSE_PRIORITE() usleep(250 * 1000)

void* staticSeConnecterThreadCallback(void* arg) {
	BASSE_PRIORITE();

	PublisherMQTT* mqtt = (PublisherMQTT*) arg;
	mqtt->seConnecter();

	return nullptr;
}

void* staticPublierThreadCallback(void* arg) {
	BASSE_PRIORITE();

	PublisherMQTT* mqtt = (PublisherMQTT*) arg;
	mqtt->publier();

	return nullptr;
}