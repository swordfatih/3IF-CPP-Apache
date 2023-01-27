/*************************************************************************
                           Analyseur  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Analyseur> (fichier Analyseur.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Analyseur.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Analyseur::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

//------------------------------------------------- Surcharge d'opérateurs
Analyseur & Analyseur::operator = ( const Analyseur & unAnalyseur )
// Algorithme :
//
{
} //----- Fin de operator =

//-------------------------------------------- Constructeurs - destructeur
Analyseur::Analyseur ( const Analyseur & unAnalyseur )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Analyseur>" << endl;
#endif
} //----- Fin de Analyseur (constructeur de copie)

Analyseur::Analyseur ( Interpreteur* destination ) : destination(destination)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Analyseur>" << endl;
#endif
} //----- Fin de Analyseur

Analyseur::~Analyseur ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Analyseur>" << endl;
#endif
} //----- Fin de ~Analyseur

void Analyseur::analyser(const string& ligne)
{
    Log log;


    destination->traiter(log);
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

