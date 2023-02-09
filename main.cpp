
#include "Analyseur.h"
#include "Statistiques.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
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
        if(argv[i][0] == '-')
        {
            if(std::strcmp(argv[i], "-g") == 0)
            {
                graphviz = true;

                if(i + 1 >= argc || argv[i + 1][0] == '-')
                {   
                    std::cerr << "[Erreur EMISSOUT] Le nom du fichier de sortie pour GraphViz est introuvable" << std::endl;
                    return 1;
                }

                chemin_sortie = argv[++i];
            }
            else if(std::strcmp(argv[i], "-e") == 0)
            {
                extension = true; 
            }
            else if(std::strcmp(argv[i], "-t") == 0)
            { 
                if(i + 1 >= argc || argv[i + 1][0] == '-')
                {   
                    std::cerr << "[Erreur EMISSHOUR] L’heure de début du créneau est manquante" << std::endl;
                    return 1;
                }

                char* result;
                heure = std::strtol(argv[++i], &result, 10);

                if(*result || heure < 0 || heure > 23)
                {
                    std::cerr << "[Erreur EWRONGHOUR] L’heure doit etre un entier entre 0 et 23" << std::endl;
                    return 1;
                }
            }
            else
            {
                std::cerr << "[Erreur EUNKOPT] L’option " << argv[i] << " est inconnu" << std::endl;
                return 1;
            }
        }
        else 
        {
            chemin_entree = argv[i];
        }    
    }

    if(chemin_entree.empty())
    {
        std::cerr << "[Erreur EMISSIN] Le nom du fichier est absent (usage : analog [options] nomdufichier)" << std::endl;
        return 1;
    }

    Config config = charger_config(".conf");
     
    Analyseur analyseur(chemin_entree);

    if(!analyseur)
    {
        std::cerr << "[Erreur EOPEN] Le fichier n’a pas pu etre ouvert" << std::endl;
        return 1;
    }

    Statistiques statistiques(config.domaine, extension, heure);
    analyseur >> &statistiques;

    analyseur.close();

    if(graphviz)
    {
        std::ofstream out(chemin_sortie);

        if(!out)
        {
            std::cerr << "[Erreur EIMPWRITE] L’ecriture dans le fichier " << chemin_sortie << " est impossible" << std::endl;
            return 1;
        }
        
        statistiques.graphe(out);
        std::cout << "Dot-file " << chemin_sortie << " generated" << std::endl;
    }

    if(heure != -1)
    {
        std::cout << "Warning : only hits between " << heure << "h and " << heure + 1 << "h have been taken into account" << std::endl;
    }
    
    statistiques.classement();
   
    return 0;
}