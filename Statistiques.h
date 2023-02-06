/*************************************************************************
                           Statistiques  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Statistiques> (fichier Statistiques.h) ----------------
#if ! defined ( STATISTIQUES_H )
#define STATISTIQUES_H

//--------------------------------------------------- Interfaces utilisées
#include "Interpreteur.h"

#include <unordered_map>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
#include <fstream>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Statistiques>
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

    Statistiques (const std::string& domaine, bool extension = false, int heure = -1);
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

    void classement();
    void graphe(const std::string& chemin_sortie);

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    std::string formatage(std::string source);

//----------------------------------------------------- Attributs protégés
    const std::array<std::string, 7> blacklist{"js", "css", "png", "jpg", "jpeg", "gif", "ico"};
    std::unordered_map<std::string, int> documents;
    std::map<std::pair<std::string, std::string>, int> noeuds;
    std::set<std::string> pages;

    std::string domaine;
    bool extension;
    int heure;

};

//-------------------------------- Autres définitions dépendantes de <Statistiques>

#endif // STATISTIQUES_H

