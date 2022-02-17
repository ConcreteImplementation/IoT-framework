#include <string.h>

#include <ArduinoJson.h>

#include "Cadriciel/Message.h"

Message::Message()
	: m_donnees(),
		m_messageErreur()
{ ; }


void Message::vider() {
	m_donnees.clear();
	m_messageErreur.clear();
}



bool Message::reussitObtenir(const char* p_nom, float* p_sortie) {
	m_iterateurDonnees = m_donnees.find(p_nom);
	if(m_iterateurDonnees == m_donnees.end()) {
		return false;
	}

	*p_sortie = m_iterateurDonnees->second;
	return true;
}

void Message::ajouterDonnee(const char* p_nom, float p_donnee) {
	std::pair<const char*, float> donnee(p_nom, p_donnee);
	m_donnees.insert(donnee);
}


const char* Message::obtenirPremiereErreur() {
	if(m_messageErreur.size() > 0)
		return m_messageErreur.front();
	return "";

}

void Message::ajouterMessage(const char* p_message) {
	m_messageErreur.push_back(p_message);
}




const char* Message::versJson() {
	DynamicJsonDocument document(2048);

	for(ITERATEUR_DONNEES it = m_donnees.begin(); it != m_donnees.end(); ++it) {
		document[it->first] = it->second;
	}

	ITERATEUR_MESSAGE it = m_messageErreur.begin();
	int i = 0;
	while(it != m_messageErreur.end()) {
		char nom[20];
		snprintf(nom, 20, "message%d", i);
		document[nom] = *it;
		
		++it;
		++i;
	}

	if(document.size() <= 0) return "";
#if EST_DEBUG
	serializeJsonPretty(document, m_json, 2048);
#else
	serializeJson(document, m_json, 2048);
#endif

	return m_json;
}