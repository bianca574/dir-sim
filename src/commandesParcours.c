#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataNode.h"
#include <stdbool.h>

#include "utile.h"

#include "commandesParcours.h"

#include "ouvrirFichier.h"

int cd(const char *chem)
{
    if (chem == NULL || strlen(chem) == 0 || strcmp(chem, "/") == 0)
    {
        noeudCourant = noeudCourant->racine;
        return OK;
    }
    noeud *cible = trouver_noeud(chem);

    if (cible == NULL)
    {
        erreur();
        printf("Le dossier %s n'existe pas.\n", chem);
        return ERREUR_EXECUTION;
    }

    if (!cible->est_dossier)
    {
        erreur();
        printf("%s n'est pas un dossier.\n", chem);
        return ERREUR_EXECUTION;;
    }
    noeudCourant = cible;
    return OK;
}