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

    // Incrémentation du nombre de visite du document
    visites[requete.url] = visites.count(requete.url) ? visites[requete.url] + 1 : 1;

    // On affiche seulement les redirections locales
    if(requete.referer.find(domaine) == 0) 
    {
        std::string&& referer = formatage(requete.referer);
        std::pair<std::string, std::string> paire(referer, requete.url);
        arcs[paire] = arcs.count(paire) ? arcs[paire] + 1 : 1;
 
        noeuds.insert(referer);
        noeuds.insert(requete.url);
    }
}

void Statistiques::classement()
{
    std::vector<std::pair<std::string, int>> valeurs;

    std::unordered_map<std::string, int>::iterator it;
    for(it = visites.begin(); it != visites.end(); ++it)
    {
        valeurs.push_back(std::make_pair(it->first, it->second));
    }

    std::sort(valeurs.begin(), valeurs.end(), [&](const std::pair<std::string, int>& f, const std::pair<std::string, int>& s) -> bool {
        return f.second > s.second;
    });

    for(unsigned int i = 0; i < (valeurs.size() > 10 ? 10 : valeurs.size()); ++i)
    {
        std::cout << valeurs[i].first << " (" << valeurs[i].second << " hits)" << std::endl;
    }
}

void Statistiques::graphe(std::ostream& out)
{
    if(out)
    {
        out << "digraph {" << std::endl;

        std::set<std::string>::iterator it_noeuds;
        for(it_noeuds = noeuds.begin(); it_noeuds != noeuds.end(); ++it_noeuds)
        {
            out << "noeud" << std::distance(noeuds.begin(), it_noeuds) << " [label=\"" << *it_noeuds << "\"];" << std::endl;
        }

        std::map<std::pair<std::string, std::string>, int>::iterator it_arcs;
        for(it_arcs = arcs.begin(); it_arcs != arcs.end(); ++it_arcs)
        {
            out << "noeud" << std::distance(noeuds.begin(), noeuds.find(it_arcs->first.first)) 
                << " -> " 
                << "noeud" << std::distance(noeuds.begin(), noeuds.find(it_arcs->first.second)) 
                << " [label=\"" << it_arcs->second << "\"];" 
                << std::endl;
        }

        out << "}";
    }
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

std::string Statistiques::formatage(std::string source)
{
    // Les performances de std::regex ralentissent le programme
    // Il vaut mieux utiliser des find et des substr

    // std::smatch result;
    // std::regex_search(source, result, std::regex(R"(//[a-z.-]*(/.*))"));
    // return result[result.size() - 1];

    size_t protocol = source.find("//");
    if(protocol != std::string::npos)
    {
        source = source.substr(protocol + 1);
    }

    size_t page = source.find("/", 1);
    if(page != std::string::npos)
    {
        source = source.substr(page);
    }   

    size_t query = source.find("?");
    if(query != std::string::npos)
    {
        source = source.substr(0, query);
    }

    query = source.find(";");
    if(query != std::string::npos)
    {
        source = source.substr(0, query);
    }

    return source;
}