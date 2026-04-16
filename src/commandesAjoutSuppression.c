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
    nouveauDossier->racine = noeudCourant->racine;
    nouveauDossier->fils = NULL;

    ajouterFilsANoeudCourant(nouveauDossier);
}

void touch(const char *nom ){
    if (nom[0]=='\0'){
        printf("Attention le nom d'un fichier a été ajouté mais il est incorrect ! Le nom de ce fichier est vide. Changez le !!\n");
        exit(1);
    }
    noeud *nouveaufichier;
    nouveaufichier = malloc(sizeof(noeud));
    if (nouveaufichier == NULL){
        printf("Echec d'allocation du fichier");
        exit(1);
    }
    nouveaufichier->est_dossier = false;
    strncpy(nouveaufichier->nom, nom, 99);
    nouveaufichier->nom[99]= '\0';
    nouveaufichier-> pere = noeudCourant;
    nouveaufichier-> racine = noeudCourant->racine;
    nouveaufichier->fils = NULL;

    ajouterFilsANoeudCourant(nouveaufichier);

}

