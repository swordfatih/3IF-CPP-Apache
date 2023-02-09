/*************************************************************************
    Analyseur  -  classe permettant de lire un fichier de log Apache
                             -------------------
    copyright            : (C) 2023 par Fatih et Nihal
*************************************************************************/

//---------- Interface de la classe <Analyseur> (fichier Analyseur.h) ----------------
#if ! defined ( ANALYSEUR_H )
#define ANALYSEUR_H

//--------------------------------------------------- Interfaces utilisées
#include "Interpreteur.h"
#include <string>
#include <fstream>

//------------------------------------------------------------------------
// Rôle de la classe <Analyseur>
//
// Classe permettant de lire un fichier de log Apache
//------------------------------------------------------------------------

class Analyseur : public std::ifstream
{
//----------------------------------------------------------------- PUBLIC

public:

//------------------------------------------------- Surcharge d'opérateurs
    Analyseur& operator>>(Interpreteur* destination);
    // Mode d'emploi : Surcharge de l'opérateur >> qui fait appel à
    // la fonction analyser
    //
    // Contrat : destination est un pointeur valide

//-------------------------------------------- Constructeurs - destructeur
    Analyseur (const std::string& path);
    // Mode d'emploi : Constructeur de la classe Analyseur, fait appel au
    // constructeur de la classe parente
    //
    // Contrat : path est un chemin valide vers un fichier de log Apache

//----------------------------------------------------- Méthodes publiques
    Log analyser(const std::string& ligne);
    // Mode d'emploi : La fonction analyser range les informations de la ligne
    // donnée en paramètre dans une structure de type Log
    //
    // Contrat : La ligne est au format Apache et ne contient pas de retour
    // à la ligne
};

#endif // ANALYSEUR_H

