#pragma once

#include <list>
#include <map>

#define ITERATEUR_MESSAGE std::list<const char*>::iterator
#define ITERATEUR_DONNEES std::map<const char*, float>::iterator

class Message {
private:
	std::map<const char*, float> m_donnees;
	std::list<const char*> m_messageErreur;

	ITERATEUR_MESSAGE m_iterateurMessages;
	ITERATEUR_DONNEES m_iterateurDonnees;

	char m_json[2048];

public:
	Message();
	void vider();

	bool reussitObtenir(const char* p_nom, float* p_sortie);
	void ajouterDonnee(const char* p_nom, float p_donnee);

	const char* obtenirPremiereErreur();
	void ajouterMessage(const char* p_message);

	const char* versJson();
};