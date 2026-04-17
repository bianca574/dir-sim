#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataNode.h"
#include <stdbool.h>

#include "commandesParcours.h"

void cd(const char *chem)
{
    if (chem == NULL || strlen(chem) == 0 || strcmp(chem, "/") == 0)
    {
        noeudCourant = noeudCourant->racine;
        return;
    }
    char *copie_chem = malloc((strlen(chem) + 1) * sizeof(char));

    if (copie_chem == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        exit(1);
    }

    strcpy(copie_chem, chem);

    noeud *actuel;

    if (chem[0] == '/')
    {
        actuel = noeudCourant->racine;
    }
    else
    {
        actuel = noeudCourant;
    }

    char *chemin = strtok(copie_chem, "/");

    while (chemin != NULL)
    {
        if (strcmp(chemin, "..") == 0)
        {
            actuel = actuel->pere;
        }
        else if (strcmp(chemin, ".") == 0)
        {
        }
        else
        {
            liste_noeud *liste = actuel->fils;
            noeud *trouve = NULL;

            while (liste != NULL)
            {
                if (strcmp(liste->no->nom, chemin) == 0)
                {
                    trouve = liste->no;
                    break;
                }
                liste = liste->succ;
            }
            if (trouve == NULL || !trouve->est_dossier)
            {
                printf("Erreur : chemin invalide.\n");
                free(copie_chem);
                exit(1);
            }
            actuel = trouve;
        }
        chemin = strtok(NULL, "/");
    }
    noeudCourant = actuel;
    free(copie_chem);
}