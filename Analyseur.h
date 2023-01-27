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

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Analyseur>
//
//
//------------------------------------------------------------------------

class Analyseur
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
    Analyseur & operator = ( const Analyseur & unXxx );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Analyseur ( const Analyseur & unXxx );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Analyseur (const Interpreteur* destination);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Analyseur ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    const Interpreteur* destination;

};

//-------------------------------- Autres définitions dépendantes de <Analyseur>

#endif // ANALYSEUR_H

