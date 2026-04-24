#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataNode.h"
#include <stdbool.h>

#include "utile.h"

#include "commandesParcours.h"

void cd(const char *chem)
{
    if (chem == NULL || strlen(chem) == 0 || strcmp(chem, "/") == 0)
    {
        noeudCourant = noeudCourant->racine;
        return;
    }
    noeud *cible = trouver_noeud(chem);

    if (cible == NULL)
    {
        printf("Erreur : le dossier n'existe pas.\n");
        exit(1);
    }

    if (!cible->est_dossier)
    {
        printf("Erreur : %s n'est pas un dossier.\n", chem);
        exit(1);
    }
    noeudCourant = cible;
}