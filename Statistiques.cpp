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

Statistiques::Statistiques (bool extension, int heure) : extension(extension), heure(heure)
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
    if(documents.count(requete.url) == 0)
        documents[requete.url] = 1;
    else
        documents[requete.url]++;

    std::pair<std::string, std::string> paire(requete.referer, requete.url);

    if(noeuds.count(paire) == 0)
        noeuds[paire] = 1;
    else
        noeuds[paire]++;

    pages.insert(requete.referer);
    pages.insert(requete.url);
}

void Statistiques::generate_scoreboard()
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

    for(unsigned int i = 0; i < valeurs.size(); ++i)
    {
        std::cout << valeurs[i].first << " " << valeurs[i].second << std::endl;
    }
}

std::string format(std::string input)
{
    if(input.rfind('/') != std::string::npos)
        input = input.substr(input.rfind('/'));

    std::string formatted;
    for(int i = 0; i < input.size(); ++i)
    {
        char c = input[i];
        if(c != '.' && c != '/' && c != '-' && c != ':')
        {
            formatted += c;
        }
    }

    return formatted;
}

void Statistiques::generate_dot(const std::string& chemin_sortie)
{
    std::cout << "Dot-file " << chemin_sortie << " generated" << std::endl;

    std::ofstream out(chemin_sortie);

    if(out)
    {
        out << "digraph {" << std::endl;

        std::set<std::string>::iterator it_pages;
        for(it_pages = pages.begin(); it_pages != pages.end(); ++it_pages)
        {
            out << format(*it_pages) << " [label=\"" << format(*it_pages) << "\"];" << std::endl;
        }

        std::map<std::pair<std::string, std::string>, int>::iterator it_noeuds;
        for(it_noeuds = noeuds.begin(); it_noeuds != noeuds.end(); ++it_noeuds)
        {
            out << format(it_noeuds->first.first) << " -> " << format(it_noeuds->first.second) << " [label=\"" << it_noeuds->second << "\"];" << std::endl;
        }

        out << "}" << std::endl;
    }
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

