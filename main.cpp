#include <iostream>

#include "Analyseur.h"
#include "Statistiques.h"

int main()
{
    Analyseur analyseur("logs.txt");

    Interpreteur* interpreteur = new Statistiques();
    analyseur >> interpreteur;

    analyseur.close();

    return 0;
}