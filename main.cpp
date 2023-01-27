
#include "Analyseur.h"
#include "Statistiques.h"
#include <iostream>
#include <string.h>
#include <string>

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
     
    Analyseur analyseur(chemin_entree);

    Statistiques statistiques(extension, heure);
    analyseur >> &statistiques;

    analyseur.close();

    if(graphviz)
    {
        statistiques.generate_dot(chemin_sortie);
    }
    
    statistiques.generate_scoreboard();
   
    return 0;
}