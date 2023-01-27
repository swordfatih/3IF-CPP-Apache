/*************************************************************************
                           Interpreteur  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Interpreteur> (fichier Interpreteur.h) ----------------
#if ! defined ( INTERPRETEUR_H )
#define INTERPRETEUR_H

//--------------------------------------------------- Interfaces utilisées
#include "Log.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Interpreteur>
//
// Classe abstraite
//------------------------------------------------------------------------

class Interpreteur
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
    Interpreteur & operator = ( const Interpreteur & unInterpreteur );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Interpreteur ( const Interpreteur & unInterpreteur ) = default;
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Interpreteur ( ) = default;
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Interpreteur () = 0;
    // Mode d'emploi : Destructeur abstraite
    //
    // Contrat :
    //

    virtual void traiter(const Log& requete) = 0;

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <Interpreteur>

#endif // INTERPRETEUR_H

