/*************************************************************************
        Interpreteur  -  classe abstraite qui sert de parent pour toutes 
        les classes traitant des logs Apache.
                             -------------------
    copyright            : (C) 2023 par Fatih et Nihal
*************************************************************************/

//---------- Réalisation de la classe <Interpreteur> (fichier Interpreteur.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Interpreteur.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
Interpreteur::~Interpreteur ( )
// Algorithme : Destructeur par défaut
{
#ifdef MAP
    cout << "Appel au destructeur de <Interpreteur>" << endl;
#endif
} //----- Fin de ~Interpreteur