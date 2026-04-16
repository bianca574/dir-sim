#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "commandesAffiche.h"
#include "commandesAjoutSuppression.h"
#include "commandesParcours.h"
#include "utile.h"

noeud *noeudCourant = NULL;

void init(){
    noeudCourant = malloc(sizeof(noeud));
    if (noeudCourant == NULL)
    {
        printf("Échec d'allocation\n");
        exit(1);
    }
    noeudCourant->est_dossier = true;
    noeudCourant->nom[0] = '\0';
    noeudCourant->pere = noeudCourant;
    noeudCourant->racine = noeudCourant;
    noeudCourant->fils = NULL;
}

int main()
{
    printf("ok\n");
    init();
    ls();
    mkdir("Test2");
    ls();

    return 0;
}
