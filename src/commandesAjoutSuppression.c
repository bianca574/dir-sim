#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataNode.h"
#include <stdbool.h>

#include "utile.h"

#include "commandesAjoutSuppression.h"


void mkdir(const char *nom){
    noeud *nouveauDossier;
    nouveauDossier = malloc(sizeof(noeud));
    if (nouveauDossier == NULL){
        printf("Échec d'allocation\n");
        exit(1);
    }
    nouveauDossier->est_dossier = true;
    strncpy(nouveauDossier->nom, nom, 99);
    nouveauDossier->nom[99] = '\0';
    nouveauDossier->pere = noeudCourant;
    nouveauDossier->fils = NULL;

    ajouterFilsANoeudCourant(nouveauDossier);
}
