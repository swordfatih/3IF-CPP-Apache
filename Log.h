/*************************************************************************
    Log  -  structure représentant les informations d'une requête HTTP
                             -------------------
    copyright            : (C) 2023 par Fatih et Nihal
*************************************************************************/

//---------- Interface de la classe <Log> (fichier Log.h) ----------------
#if ! defined ( LOG_H )
#define LOG_H

//--------------------------------------------------- Interfaces utilisées
#include <string>

//------------------------------------------------------------------------
// Rôle de la structure <Log>
//
// Structure représentant les informations d'une requête HTTP
//------------------------------------------------------------------------

struct Log
{
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Attributs publiques
    std::string ip;
    std::string log_name;
    std::string auth_name;
    std::string date;
    unsigned int heure;
    std::string shift;
    std::string action;
    std::string url;
    std::string version;
    std::string status;
    size_t size;
    std::string referer;
    std::string client;

};

#endif // LOG_H

