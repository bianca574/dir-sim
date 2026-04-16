#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataNode.h"
#include <stdbool.h>

#include "utile.h"
 
// ajout à la fin de fils
void ajouterFilsANoeudCourant(noeud *nouveauFils){
    if (noeudCourant->fils == NULL){
        noeudCourant->fils = malloc(sizeof(liste_noeud));
        noeudCourant->fils->no = nouveauFils;
        noeudCourant->fils->succ = NULL;
    }
    else{
        liste_noeud *copie = noeudCourant->fils;
        while (copie->succ != NULL){
            copie = copie->succ;
        }
        copie->succ = malloc(sizeof(liste_noeud));
        copie->succ->no = nouveauFils;
        copie->succ->succ = NULL;
    }
}


