/*************************************************************************
        Interpreteur  -  classe abstraite qui sert de parent pour toutes 
        les classes traitant des logs Apache.
                             -------------------
    copyright            : (C) 2023 par Fatih et Nihal
*************************************************************************/

//---------- Interface de la classe <Interpreteur> (fichier Interpreteur.h) ----------------
#if ! defined ( INTERPRETEUR_H )
#define INTERPRETEUR_H

//--------------------------------------------------- Interfaces utilisées
#include "Log.h"

//------------------------------------------------------------------------
// Rôle de la classe <Interpreteur>
//
// Classe abstraite qui sert de parent pour toutes 
// les classes traitant des logs Apache.
//------------------------------------------------------------------------

class Interpreteur
{
//----------------------------------------------------------------- PUBLIC

public:
//-------------------------------------------- Constructeurs - destructeur
    virtual ~Interpreteur () = 0;
    // Mode d'emploi : Destructeur par défaut purement virtuelle

//----------------------------------------------------- Méthodes publiques
    virtual void traiter(const Log& requete) = 0;
    // Mode d'emploi : Fonction qui a pour rôle de traiter un log Apache.
    //
    // Contrat : Les champs de la requête sont correctement remplis.
};

#endif // INTERPRETEUR_H

