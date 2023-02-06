
#include "Analyseur.h"
#include "Statistiques.h"
#include <iostream>
#include <string.h>
#include <string>
#include <fstream>

struct Config
{
    std::string domaine = "http://intranet-if.insa-lyon.fr/";
};

Config charger_config(const std::string& chemin)
{
    Config config;

    std::ifstream file(chemin);
    if(file)
    {
        std::string ligne;
        while(std::getline(file, ligne))
        {
            std::string key = ligne.substr(0, ligne.find("="));
            std::string value = ligne.substr(ligne.find("=") + 1);

            if(key == "domaine")
            {
                config.domaine = value;
            }
        }   
    }

    return config;
}

int main(int argc, char* argv[])
{
    std::string chemin_entree, chemin_sortie;

    bool graphviz = false, extension = false;
    int heure = -1;

    for(int i = 1; i < argc; ++i) 
    {
        if(strcmp(argv[i], "-g") == 0)
        {
            graphviz = true;
            chemin_sortie = argv[++i];
        }
        else if(strcmp(argv[i], "-e") == 0)
        {
            extension = true; 
        }
        else if(strcmp(argv[i], "-t") == 0)
        { 
            std::string token(argv[++i]);
            heure = std::stoi(token);
        }
        else 
        {
            chemin_entree = argv[i];
        }    
    }

    Config config = charger_config(".env");
     
    Analyseur analyseur(chemin_entree);

    Statistiques statistiques(config.domaine, extension, heure);
    analyseur >> &statistiques;

    analyseur.close();

    if(graphviz)
    {
        statistiques.graphe(chemin_sortie);
    }
    
    statistiques.classement();
   
    return 0;
}