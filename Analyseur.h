/*************************************************************************
                           Analyseur  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Analyseur> (fichier Analyseur.h) ----------------
#if ! defined ( ANALYSEUR_H )
#define ANALYSEUR_H

//--------------------------------------------------- Interfaces utilisées
#include "Interpreteur.h"
#include <string>
#include <fstream>
#include <vector>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Analyseur>
//
//
//------------------------------------------------------------------------

class Analyseur : public std::ifstream
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs
    Analyseur& operator>>(Interpreteur* destination);

//-------------------------------------------- Constructeurs - destructeur
    Analyseur ( const Analyseur & unXxx );

    Analyseur (const std::string& path);
    // Mode d'emploi :
    //
    // Contrat :
    //

    Log analyser(const std::string& ligne);

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
};

//-------------------------------- Autres définitions dépendantes de <Analyseur>

#endif // ANALYSEUR_H

