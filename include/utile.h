#ifndef UTILE_H
#define UTILE_H

#include "dataNode.h"

void ajouterFilsANoeudCourant(noeud *parent, noeud *nouveauFils);
void free_noeud(noeud *noeud);
noeud *trouver_noeud(const char *chem);
void separer_chemin(const char *chem, char *nouveau_chem, char *nom_fic);
bool est_ancetre(noeud *potentiel_ancetre, noeud *depart);
noeud *chercher_fils(noeud *parent, const char *nom);
void retirer_fils(noeud *parent, noeud *cible);

#endif