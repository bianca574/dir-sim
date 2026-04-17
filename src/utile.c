#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataNode.h"
#include <stdbool.h>

#include "utile.h"

// ajout à la fin de fils
void ajouterFilsANoeudCourant(noeud *nouveauFils)
{
    if (noeudCourant->fils == NULL)
    {
        noeudCourant->fils = malloc(sizeof(liste_noeud));
        noeudCourant->fils->no = nouveauFils;
        noeudCourant->fils->succ = NULL;
    }
    else
    {
        liste_noeud *copie = noeudCourant->fils;
        while (copie->succ != NULL)
        {
            copie = copie->succ;
        }
        copie->succ = malloc(sizeof(liste_noeud));
        copie->succ->no = nouveauFils;
        copie->succ->succ = NULL;
    }
}

void free_noeud(noeud *noeud)
{
    if (noeud == NULL)
    {
        return;
    }
    liste_noeud *copie = noeud->fils;
    while (copie != NULL)
    {
        liste_noeud *suivant = copie->succ;
        free_noeud(copie->no);
        free(copie);
        copie = suivant;
    }
    free(noeud);
}

noeud *trouver_noeud(const char *chem)
{
    if (chem == NULL || strlen(chem) == 0)
    {
        return NULL;
    }

    char *copie_chem = malloc((strlen(chem) + 1) * sizeof(char));

    if (copie_chem == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        exit(1);
    }

    strcpy(copie_chem, chem);

    char *chemin = strtok(copie_chem, "/");

    noeud *actuel = chem[0] == '/' ? noeudCourant->racine : noeudCourant;

    noeud *trouve = actuel;

    while (chemin != NULL)
    {
        if (strcmp(chemin, "..") == 0)
        {
            trouve = actuel->pere;
        }
        else if (strcmp(chemin, ".") == 0)
        {
            trouve = actuel;
        }
        else
        {
            liste_noeud *liste = actuel->fils;

            trouve = NULL;

            while (liste != NULL)
            {
                if (strcmp(liste->no->nom, chemin) == 0)
                {
                    trouve = liste->no;
                    break;
                }
                liste = liste->succ;
            }
        }
        if (trouve == NULL)
        {
            free(copie_chem);
            return NULL;
        }
        chemin = strtok(NULL, "/");

        if (chemin != NULL)
        {
            if (!trouve->est_dossier)
            {
                free(copie_chem);
                return NULL;
            }
            actuel = trouve;
        }
    }
    free(copie_chem);
    return trouve;
}
