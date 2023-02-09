/*************************************************************************
    Statistiques  -  Classe traitant des logs Apache pour en faire un 
    classement et un graphe.
                             -------------------
    copyright            : (C) 2023 par Fatih et Nihal
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
// Classe traitant des logs Apache pour en faire un classement et 
// un graphe.
//------------------------------------------------------------------------

class Statistiques: public Interpreteur
{
//----------------------------------------------------------------- PUBLIC

public:
//-------------------------------------------- Constructeurs - destructeur
    Statistiques (const std::string& domaine, bool extension = false, int heure = -1);
    // Mode d'emploi : Constructeur par défaut
    //
    // Contrat : domaine est le bon nom de domaine local du serveur Apache analysé

    virtual ~Statistiques ( );
    // Mode d'emploi : Destructeur par défaut

//----------------------------------------------------- Méthodes publiques
    void traiter(const Log& requete);
    // Mode d'emploi : Fonction qui a pour rôle de traiter un log Apache.
    //
    // Contrat : Les champs de la requête sont correctement remplis.

    void classement(std::ostream& out);
    // Mode d'emploi : Permet de générer le top 10 des URL les plus
    // visités.
    //
    // Contrat : out est une sortie vers un flux valide.

    void graphe(std::ostream& out);
    // Mode d'emploi : Permet de générer un graphe au format GraphViz
    // de toutes les redirections.
    //
    // Contrat : out est une sortie vers un flux valide.

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    std::string formatage(std::string source);
    // Mode d'emploi : Permet de transformer une adresse URL complète vers
    // un format plus compact, utile pour les adresses locales
    //
    // Contrat : source est un url valide qui commence par la valeur de 
    // domaine

//----------------------------------------------------- Attributs protégés
    const std::array<std::string, 7> blacklist{"js", "css", "png", "jpg", "jpeg", "gif", "ico"};    ///< Les formats à exclure lorsque l'option est appliquée
    
    std::unordered_map<std::string, int> visites;               ///< Le nombre de visites pour une page donnée
    std::map<std::pair<std::string, std::string>, int> arcs;    ///< Le nombre de redirection pour une source et une destination donnée
    std::set<std::string> noeuds;                               ///< L'ensemble de tous les sources et destinations

    std::string domaine;    ///< Le domaine local du serveur Apache
    bool extension;         ///< Vrai si l'option extension est activée
    int heure;              ///< -1 si l'option heure est désactivée, sinon contient l'heure à filtrer

};

#endif // STATISTIQUES_H

