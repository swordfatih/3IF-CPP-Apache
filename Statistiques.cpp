/*************************************************************************
                           Statistiques  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Statistiques> (fichier Statistiques.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <regex>

//------------------------------------------------------ Include personnel
#include "Statistiques.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Xxx::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs
Statistiques & Statistiques::operator = ( const Statistiques & unStatistiques )
// Algorithme :
//
{
    return *this;
} //----- Fin de operator =

//-------------------------------------------- Constructeurs - destructeur
Statistiques::Statistiques ( const Statistiques & unStatistiques )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Xxx>" << endl;
#endif
} //----- Fin de Xxx (constructeur de copie)

Statistiques::Statistiques (const std::string& domaine, bool extension, int heure) : domaine(domaine), extension(extension), heure(heure)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Xxx>" << endl;
#endif
} //----- Fin de Xxx


Statistiques::~Statistiques ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Xxx>" << endl;
#endif
} //----- Fin de ~Xxx

void Statistiques::traiter(const Log& requete)
{
    // Condition pour filtrer sur l'extension ou sur l'heure
    if((extension && std::find(blacklist.begin(), blacklist.end(), requete.url.substr(requete.url.rfind('.') + 1)) != blacklist.end())
        || (heure != -1 && heure != requete.heure))
    {
        return;    
    }

    documents[requete.url] = documents.count(requete.url) ? documents[requete.url] + 1 : 1;

    // On affiche seulement les redirections locales
    if(requete.referer.find(domaine) == 0) 
    {
        std::smatch result;
        std::regex_search(requete.referer, result, std::regex(R"(//[a-z.-]*(/.*))"));

        std::string&& referer = result[result.size() - 1];
        std::pair<std::string, std::string> paire(referer, requete.url);
        noeuds[paire] = noeuds.count(paire) ? noeuds[paire] + 1 : 1;
 
        pages.insert(referer);
        pages.insert(requete.url);
    }
}

void Statistiques::classement()
{
    std::vector<std::pair<std::string, int>> valeurs;

    std::unordered_map<std::string, int>::iterator it;
    for(it = documents.begin(); it != documents.end(); ++it)
    {
        valeurs.push_back(std::make_pair(it->first, it->second));
    }

    std::sort(valeurs.begin(), valeurs.end(), [&](const std::pair<std::string, int>& f, std::pair<std::string, int>& s) -> bool {
        return f.second > s.second;
    });

    for(unsigned int i = 0; i < (valeurs.size() > 10 ? 10 : valeurs.size()); ++i)
    {
        std::cout << valeurs[i].first << " " << valeurs[i].second << std::endl;
    }
}

void Statistiques::graphe(std::ostream& out)
{
    if(out)
    {
        out << "digraph {" << std::endl;

        std::set<std::string>::iterator it_pages;
        for(it_pages = pages.begin(); it_pages != pages.end(); ++it_pages)
        {
            out << "noeud" << std::distance(pages.begin(), it_pages) << " [label=\"" << *it_pages << "\"];" << std::endl;
        }

        std::map<std::pair<std::string, std::string>, int>::iterator it_noeuds;
        for(it_noeuds = noeuds.begin(); it_noeuds != noeuds.end(); ++it_noeuds)
        {
            out << "noeud" << std::distance(pages.begin(), pages.find(it_noeuds->first.first)) 
                << " -> " 
                << "noeud" << std::distance(pages.begin(), pages.find(it_noeuds->first.second)) 
                << " [label=\"" << it_noeuds->second << "\"];" 
                << std::endl;
        }

        out << "}" << std::endl;
    }
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

std::string Statistiques::formatage(std::string source)
{

}

