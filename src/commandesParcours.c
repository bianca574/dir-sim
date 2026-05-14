#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataNode.h"
#include <stdbool.h>

#include "utile.h"

#include "commandesParcours.h"

#include "ouvrirFichier.h"

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
        erreur();
        printf("Le dossier %s n'existe pas.\n", chem);
        exit(1);
    }

    if (!cible->est_dossier)
    {
        erreur();
        printf("%s n'est pas un dossier.\n", chem);
        exit(1);
    }
    noeudCourant = cible;
}