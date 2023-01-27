/*************************************************************************
                           Xxx  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Xxx> (fichier Xxx.h) ----------------
#if ! defined ( STATISTIQUES_H )
#define STATISTIQUES_H

//--------------------------------------------------- Interfaces utilisées
#include "Interpreteur.h"

#include <unordered_map>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Xxx>
//
//
//------------------------------------------------------------------------

class Statistiques: public Interpreteur
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
   Statistiques & operator = ( const Statistiques & unStatistiques );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Statistiques ( const Statistiques & unStatistiques);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Statistiques (bool extension = false, bool graphe = false, bool temps = false);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Statistiques ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void traiter(const Log& requete);

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    std::unordered_map<std::string, int> documents;
    std::unordered_map<std::pair<std::string, std::string>, int> graphe;

    bool extension;
    bool graphe;
    bool temps;

};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // XXX_H

