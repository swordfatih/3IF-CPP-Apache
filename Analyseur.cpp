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

Analyseur::Analyseur (const std::string& path) : std::ifstream(path)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Analyseur>" << endl;
#endif
} //----- Fin de Analyseur

Analyseur & Analyseur::operator >> (Interpreteur* destination)
{
    if(!is_open())
        return *this;

    std::string ligne;

    while(std::getline(*this, ligne))
    {
        destination->traiter(analyser(ligne));
    }   

    return *this;
}

Log Analyseur::analyser(const std::string& ligne)
{
    Log log;
    
    std::string format;

    for(unsigned int i = 0; i < ligne.size(); ++i)
    {
        char c = ligne.at(i);
        if(c != '[' && c != ']' && c != '"')
            format += c;
    }
    
    format[format.find(':')] = ' ';
    std::stringstream stream(format);

    std::string token;

    std::getline(stream, log.ip, ' ');
    std::getline(stream, log.log_name, ' ');
    std::getline(stream, log.auth_name, ' ');
    std::getline(stream, log.date, ' ');

    std::getline(stream, token, ' ');
    std::stringstream heure_stream(token);
    std::getline(heure_stream, token, ':');
    log.heure = std::stoi(token);

    std::getline(stream, log.shift, ' ');
    std::getline(stream, log.action, ' ');
    std::getline(stream, log.url, ' ');
    std::getline(stream, log.version, ' ');
    std::getline(stream, log.status, ' ');

    std::getline(stream, token, ' ');
    log.size = std::stoll(token);

    std::getline(stream, log.referer, ' ');
    std::getline(stream, log.client, ' ');

    return log;
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

