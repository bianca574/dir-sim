#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dataNode.h"
#include "commandesAffiche.h"

void ls()
{
    liste_noeud *copie = noeudCourant->fils;
    while (copie != NULL)
    {
        printf("%s \n", copie->no->nom);
        copie = copie->succ;
    }
}

void pwd()
{
}
