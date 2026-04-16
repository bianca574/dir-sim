#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataNode.h"


//ajout à la fin de fils
void ajouterFilsANoeudCourant(noeud *nouveauFils){
    if (noeudCourant->fils==NULL){
        noeudCourant->fils = malloc(sizeof(liste_noeud));
        noeudCourant->fils->no = nouveauFils;
        noeudCourant->fils->succ = NULL;
        
    }
    else {
        liste_noeud *copie= noeudCourant->fils;
        while (copie->succ != NULL){
            copie = copie->succ;
        }
        copie->succ= malloc(sizeof(liste_noeud));
        copie->succ->no = nouveauFils;
        copie->succ->succ = NULL;
    }
    

}

void mkdir(const char *nom){
    noeud *nouveauDossier;
    nouveauDossier = malloc(sizeof(noeud));
    if (nouveauDossier == NULL){
        printf("Échec d'allocation\n");
        exit(1);
    }
    nouveauDossier->est_dossier = true;
    strncpy(nouveauDossier->nom, nom, 99);
    nouveauDossier->nom[99]='\0';
    nouveauDossier->pere = noeudCourant;
    nouveauDossier->fils =NULL;

    ajouterFilsANoeudCourant(nouveauDossier);


}

void ls(){
    liste_noeud *copie = noeudCourant->fils;
    while (copie!=NULL){
        printf("%s \n", copie->no->nom);
    }
}