/*************************************************************************
                           Analyseur  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Analyseur> (fichier Analyseur.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <sstream>

//------------------------------------------------------ Include personnel
#include "Analyseur.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Analyseur::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

//------------------------------------------------- Surcharge d'opérateurs
Analyseur & Analyseur::operator = ( const Analyseur & unAnalyseur )
// Algorithme :
//
{
} //----- Fin de operator =

//-------------------------------------------- Constructeurs - destructeur
Analyseur::Analyseur ( const Analyseur & unAnalyseur )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Analyseur>" << endl;
#endif
} //----- Fin de Analyseur (constructeur de copie)

Analyseur::Analyseur ( Interpreteur* destination ) : destination(destination)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Analyseur>" << endl;
#endif
} //----- Fin de Analyseur

Analyseur::~Analyseur ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Analyseur>" << endl;
#endif
} //----- Fin de ~Analyseur

void Analyseur::analyser(const std::string& ligne)
{
    Log log;

    // ligne.ligne.find(':');

    std::stringstream stream(ligne);

    std::string token;

    std::getline(stream, log.ip, ' ');
    std::getline(stream, log.log_name, ' ');
    std::getline(stream, log.auth_name, ' ');
    std::getline(stream, log.date, ' ');

    std::getline(stream, token, ' ');
    log.heure = std::stoi(token);

    std::getline(stream, log.action, ' ');
    std::getline(stream, log.status, ' ');

    std::getline(stream, token, ' ');
    log.size = std::stoll(token);

    std::getline(stream, log.referer, ' ');
    std::getline(stream, log.client, ' ');

    destination->traiter(log);
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

