/*************************************************************************
    Analyseur  -  classe permettant d'analyser un fichier de log Apache
                             -------------------
    copyright            : (C) 2023 par Fatih et Nihal
*************************************************************************/

//---------- Réalisation de la classe <Analyseur> (fichier Analyseur.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <sstream>

//------------------------------------------------------ Include personnel
#include "Analyseur.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

Analyseur::Analyseur (const std::string& path) : std::ifstream(path)
// Algorithme : Appel au constructeur par défaut de la classe parente
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Analyseur>" << endl;
#endif
} //----- Fin de Analyseur

Analyseur & Analyseur::operator >> (Interpreteur* destination)
// Algorithme : Appel à la fonction analyser pour chaque ligne
// On passe le résultat à l'interpréteur donné en paramètre
// Qui s'occupe de traiter les logs.
{
    if(!is_open())
        return *this;

    std::string ligne;

    while(std::getline(*this, ligne))
    {
        destination->traiter(analyser(ligne));
    }   

    return *this;
} //----- Fin de operator >>

Log Analyseur::analyser(const std::string& ligne)
// Algorithme : parser la ligne avec un stringstream
// On n'utilise pas de regex à cause des faibles performances
{
    Log log;

    // On efface les caractères inutiles  
    std::string format;
    for(unsigned int i = 0; i < ligne.size(); ++i)
    {
        char c = ligne.at(i);
        if(c != '[' && c != ']' && c != '"' && !(c == ' ' && ligne.at(i - 1) == ' '))
            format += c;
    }
    
    format[format.find(':')] = ' ';

    // On extrait les informations
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

    while(std::getline(stream, token, ' '))
    {
        if(token.find("HTTP") == 0)
        {
            log.version = token;
            break;
        }
            
        if(!log.url.empty())
            log.url += ' ';

        log.url += token;
    }

    std::getline(stream, token, ' ');
    log.status = std::stoi(token);

    std::getline(stream, log.size, ' ');
    std::getline(stream, log.referer, ' ');
    std::getline(stream, log.client, '\n');

    return log;
} //----- Fin de analyser