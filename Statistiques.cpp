/*************************************************************************
    Statistiques  -  Classe traitant des logs Apache pour en faire un 
    classement et un graphe.
                             -------------------
    copyright            : (C) 2023 par Fatih et Nihal
*************************************************************************/

//---------- Réalisation de la classe <Statistiques> (fichier Statistiques.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Statistiques.h"

//----------------------------------------------------------------- PUBLIC

Statistiques::Statistiques (const std::string& domaine, bool extension, int heure) : domaine(domaine), extension(extension), heure(heure)
// Algorithme : Constructeur par défaut
{
#ifdef MAP
    cout << "Appel au constructeur de <Statistiques>" << endl;
#endif
} //----- Fin de Statistiques


Statistiques::~Statistiques ( )
// Algorithme : Destructeur par défaut
{
#ifdef MAP
    cout << "Appel au destructeur de <Statistiques>" << endl;
#endif
} //----- Fin de ~Statistiques

void Statistiques::traiter(const Log& requete)
// Algorithme : d'abord on effectue une vérification sur les filtres
// Ensuite on incrémente le nombre de visite sur l'url
// Puis on incrémente le nombre de redirection entre ces deux liens
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

void Statistiques::classement(std::ostream& out)
// Algorithme : on transfère les valeurs vers un vecteur
// On trie le vecteur puis on l'affiche
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
        out << valeurs[i].first << " (" << valeurs[i].second << " hits)" << std::endl;
    }
}

void Statistiques::graphe(std::ostream& out)
// Algorithme : on construit un fichier au format dot
// compatible avec GraphViz
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
// Algorithme : on formatte l'url avec des finds et des substr
//
// On aurait pu utiliser std::regex mais
// Les performances de std::regex ralentissent le programme
//
// Voici le code avec regex, beaucoup plus simple mais lent sur 
// des très grands fichiers de log (ce qui n'est pas rare) :
//
// std::smatch result;
// std::regex_search(source, result, std::regex(R"(//[a-z.-]*(/.*))"));
// return result[result.size() - 1];
//
{
    // on enlève le protocol du début
    size_t protocol = source.find("//");
    if(protocol != std::string::npos)
    {
        source = source.substr(protocol + 1);
    }

    // on récupère la partie relatif
    size_t page = source.find("/", 1);
    if(page != std::string::npos)
    {
        source = source.substr(page);
    }   

    // on supprime les paramètres d'URL après ?
    size_t query = source.find("?");
    if(query != std::string::npos)
    {
        source = source.substr(0, query);
    }

    // on supprime les paramètres d'URL après ;
    query = source.find(";");
    if(query != std::string::npos)
    {
        source = source.substr(0, query);
    }

    return source;
}